#pragma once

class Gun
{
public:
	enum State {
		Idle, 
		Shooting, 
		Empty, 
		Reloading,

		StateCount
	};
	static const int STATE_COUNT = (int)State::StateCount;

private:
	State mState = State::Idle;

	int mTransitions[STATE_COUNT][STATE_COUNT] =
	{
		// Idle, Shooting, Empty, Reloading, 
		{  0,    1,        0,     1 }, // Idle
		{  1,    0,        1,     1 }, // Shooting
		{  0,    0,        0,     1 }, // Empty
		{  1,    0,        0,     0 }, // Reloading
	};
	
	int mAmmo = 23;
	int mAmmoCapacity = 23;
	int mCapacity = 115;
	bool mIsReloading = false;
	bool mIsShooting = false;
	float mReloadTime = 2.5f;
	float mShootTime = 0.7f;
	float mReloadProgress = 0.0f;
	float mShootProgress = 0.0f;	

public:
	Gun(
		int _mAmmo,
		int _mCapacity,
		bool _mIsReloading,
		bool _mIsShooting,
		float _mReloadTime,
		float _mShootTime,
		float _mReloadProgress,
		float _mShootProgress
	);

	void Update(float deltatime);
	void Shoot();
	void Reload();
	void HandleInput();

	bool TransitionTo(State newState);
};
