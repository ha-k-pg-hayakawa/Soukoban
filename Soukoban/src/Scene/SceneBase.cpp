
#include "SceneBase.h"

SceneBase::SceneBase()
	: m_Step( 0 )
{
}

SceneBase::~SceneBase()
{
}

bool SceneBase::IsEnd() const
{
	return false;
}

void SceneBase::set_Step(int step_)
{
	m_Step = step_;
}

