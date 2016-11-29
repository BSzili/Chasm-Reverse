#include "../assert.hpp"
#include "../math_utils.hpp"

#include "monster_base.hpp"

namespace PanzerChasm
{

MonsterBase::MonsterBase(
	const GameResourcesConstPtr& game_resources,
	const unsigned char monster_id,
	const m_Vec3& pos,
	const float angle )
	: game_resources_(game_resources)
	, monster_id_(monster_id)
	, pos_(pos)
	, angle_( NormalizeAngle(angle) )
	, health_( game_resources_->monsters_description[ monster_id ].life )
{
	PC_ASSERT( game_resources_ != nullptr );
	PC_ASSERT( monster_id_ < game_resources_->monsters_description.size() );
}

MonsterBase::~MonsterBase()
{}

unsigned char MonsterBase::MonsterId() const
{
	return monster_id_;
}

const m_Vec3& MonsterBase::Position() const
{
	return pos_;
}

void MonsterBase::SetPosition( const m_Vec3& pos )
{
	pos_= pos;
}

float MonsterBase::Angle() const
{
	return angle_;
}

unsigned int MonsterBase::CurrentAnimation() const
{
	return current_animation_;
}

unsigned int MonsterBase::CurrentAnimationFrame() const
{
	return current_animation_frame_;
}


int MonsterBase::GetAnimation( const AnimationId id ) const
{
	PC_ASSERT( monster_id_ < game_resources_->monsters_models.size() );
	const Model& model= game_resources_->monsters_models[ monster_id_ ];

	for( const Model::Animation& animation : model.animations )
	{
		if( animation.id == static_cast<unsigned int>(id) )
			return &animation - model.animations.data();
	}
	return -1;
}

int MonsterBase::GetAnyAnimation( const std::initializer_list<AnimationId>& ids ) const
{
	for( const AnimationId id : ids )
	{
		const int  animation= GetAnimation( id );
		if( animation >= 0 )
			return animation;
	}

	return -1;
}


} // namespace PanzerChasm