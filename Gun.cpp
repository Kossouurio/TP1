#include "Gun.h"
#include <iostream>
#include <conio.h>
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
		break;

	case Gun::Shooting:
		Shoot();
		break;

	case Gun::Empty:
		if (mCapacity > 0)
		{
			TransitionTo(Gun::Reloading);
		}
		else
		{
			std::cout << "You have no ammo!" << std::endl;
			TransitionTo(Gun::Idle);
		}

		break;

	case Gun::Reloading:
		Reload();
		break;

	default:
		break;
	}
}

// Shoot() et Reload() : permettent de déclencher les actions de tir et de rechargement si les conditions le permettent.

void Gun::Shoot()
{
	//assert((mAmmo = 0) && "You have no ammo, you need to reload");
	mIsReloading = false;
	mIsShooting = true;
	mAmmo--;
	std::cout << "Bang! Ammo left: " << mAmmo << std::endl;
	if (mAmmo == 0)
	{
		TransitionTo(Gun::Empty);
	}
}

void Gun::Reload()
{
	//assert((mCapacity = 0) && "You have no ammo");

	mIsShooting = false;
	mIsReloading = true;
	std::cout << "Reloading..." << std::endl;
	
	mReloadProgress += 0.1f;

	if (mReloadProgress >= mReloadTime)
	{
		mAmmo = mCapacity;
		mReloadProgress = 0.0f;
		std::cout << "Reloaded! Ammo left: " << mAmmo << std::endl;
		TransitionTo(Gun::Idle);
	}
}

void Gun::HandleInput()
{
	if (_kbhit())
	{
		char key = _getch();
		std::cout << "Touche pressee : " << key << std::endl;
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
