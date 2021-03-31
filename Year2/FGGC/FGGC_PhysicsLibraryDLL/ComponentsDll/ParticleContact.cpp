#include "stdafx.h"
#include "ParticleContact.h"
#include "directxcollision.h"
#include <stdexcept>

ParticleContact::ParticleContact(ParticleModel* object1, ParticleModel* object2){
	mParticles[0] = object1;
	mParticles[1] = object2;
}
ParticleContact::~ParticleContact(){

}

void ParticleContact::Resolve(float duration){
	this->ResolveVelocity(duration);
	this->ResolveInterpenetration(duration);
}
float ParticleContact::CalculateSeparatingVelocity(){
	Vector3 relativeVelocity;
	relativeVelocity.x = mParticles[0]->GetVelocity().x;
	relativeVelocity.y = mParticles[0]->GetVelocity().y;
	relativeVelocity.z = mParticles[0]->GetVelocity().z;

	if (mParticles[1])	{ 
		relativeVelocity.x -= mParticles[1]->GetVelocity().x; 
		relativeVelocity.y -= mParticles[1]->GetVelocity().y; 
		relativeVelocity.z -= mParticles[1]->GetVelocity().z; 
	}

	return relativeVelocity * mContactNormal;
}

void ParticleContact::ResolveVelocity(float duration){
	float separatingVelocity = this->CalculateSeparatingVelocity();

	if (separatingVelocity > 0)	return;				// Contact is separating or stationary - no impulse

	float newSeparating = -separatingVelocity * mRestitution;
	float deltaVelocity = newSeparating - separatingVelocity;
	float totalMass = mParticles[0]->GetMass();

	if (mParticles[1])	totalMass += mParticles[1]->GetMass();
	if (totalMass <= 0) return;								

	float impulse = deltaVelocity / totalMass;

	Vector3 impulsePerMass = mContactNormal * impulse;
	
	Vector3 newOne = Vector3((Vector3(mParticles[0]->GetVelocity().x, mParticles[0]->GetVelocity().y, mParticles[0]->GetVelocity().z) + impulsePerMass * mParticles[0]->GetMass()));

	mParticles[0]->SetVelocity(XMFLOAT3(newOne.x, newOne.y, newOne.z));

	if (mParticles[1]){
		Vector3 newTwo = Vector3((Vector3(mParticles[1]->GetVelocity().x, mParticles[1]->GetVelocity().y, mParticles[1]->GetVelocity().z) + impulsePerMass * mParticles[1]->GetMass()));
		mParticles[1]->SetVelocity(XMFLOAT3(newTwo.x, newTwo.y, newTwo.z));
	}
}
void ParticleContact::ResolveInterpenetration(float duration){
	if (mPenetration <= 0) return;

	float totalMass = mParticles[0]->GetMass();

	if (mParticles[1]) totalMass += mParticles[1]->GetMass();
	if (totalMass <= 0) return;

	Vector3 movePerMass = mContactNormal * (-mPenetration / totalMass);

	Vector3 newOne = Vector3(Vector3(mParticles[0]->GetTransform()->GetPosition().x + movePerMass.x * mParticles[0]->GetMass(), mParticles[0]->GetTransform()->GetPosition().y + movePerMass.y * mParticles[0]->GetMass(), 
		mParticles[0]->GetTransform()->GetPosition().z + movePerMass.z * mParticles[0]->GetMass()));
	mParticles[0]->GetTransform()->SetPosition(newOne.x, newOne.y, newOne.z);

	if (mParticles[1]){
		Vector3 newOne = Vector3(Vector3(mParticles[1]->GetTransform()->GetPosition().x + movePerMass.x * mParticles[1]->GetMass(), mParticles[1]->GetTransform()->GetPosition().y + movePerMass.y * mParticles[1]->GetMass(),
			mParticles[1]->GetTransform()->GetPosition().z + movePerMass.z * mParticles[1]->GetMass()));
		mParticles[1]->GetTransform()->SetPosition(newOne.x, newOne.y, newOne.z);
	}

}