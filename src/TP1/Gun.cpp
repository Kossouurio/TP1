#include "Gun.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cassert>


Gun::Gun(int _mAmmo, int _mCapacity, bool _mIsReloading, bool _mIsShooting, float _mReloadTime, float _mShootTime, float _mReloadProgress, float _mShootProgress) : 
	mAmmo(_mAmmo),
	mCapacity(_mCapacity),
	mIsReloading(_mIsReloading),
	mIsShooting(_mIsShooting),
	mReloadTime(_mReloadTime),
	mShootTime(_mShootTime),
	mReloadProgress(_mReloadProgress),
	mShootProgress(_mShootProgress)
{
}

void Gun::Update(float deltatime)
{
	switch (mState)
	{
	case Gun::Idle:
		mIsReloading = false;
		mIsShooting = false;
		mReloadProgress = 0.0f;
		mShootProgress = 0.0f;
		break;

	case Gun::Shooting:
		mShootProgress += deltatime;

		if (mShootProgress >= mShootTime)
		{
			mShootProgress = 0.0f;
			mIsShooting = true;
			Shoot();
		}
		break;

	case Gun::Empty:
		std::cout << "You have no ammo!" << std::endl;
		std::cout << TransitionTo(Gun::Idle) << std::endl;
		break;

	case Gun::Reloading:
		mReloadProgress += deltatime;

		if (mReloadProgress >= mReloadTime)
		{
			mReloadProgress = 0.0f;
			mIsReloading = true;
			Reload();
		}
		break;

	default:
		break;
	}
}

// Shoot() et Reload() : permettent de déclencher les actions de tir et de rechargement si les conditions le permettent.

void Gun::Shoot()
{
	if (mAmmo > 0)
	{
		mAmmo -= 1;
		std::cout << "Bang! Ammo left: " << mAmmo << std::endl;
	}
	else
	{
		TransitionTo(Gun::Empty);
	}

}

void Gun::Reload()
{
	if ((mAmmo < mCapacity) && (mAmmo < mAmmoCapacity))
	{
		std::cout << "Reloading..." << std::endl;
		mAmmo += 1;
		mCapacity -= 1;
	}
	else
	{
		std::cout << "You are full!" << std::endl;
		TransitionTo(Gun::Idle);
	}

}

void Gun::HandleInput()
{
	if (_kbhit())
	{
		char key = _getch();
		if (key == ' ')
		{
			TransitionTo(Gun::Shooting);
		}
		if (key == 'r' || key == 'R')
		{
			TransitionTo(Gun::Reloading);
		}
		if (key == 'a' || key == 'A')
		{
			TransitionTo(Gun::Idle);
		}
		if (key == 'q' || key == 'Q')
		{
			exit(0);
		}
		if (key == 'c' || key == 'C')
		{
			std::cout << "Capacity : " << mCapacity << std::endl;
		}
	}
}

bool Gun::TransitionTo(State newState)
{
	if (mTransitions[(int)mState][(int)newState] == 0)
	{
		return false;
	}

	mState = newState;

	return true;
}
