
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

// シーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	// 処理内容は派生クラス毎に違うので、
	// 純粋仮想関数として宣言しておく
	virtual void Exec() = 0;	// 処理を行う
	virtual void Draw() = 0;	// 描画を行う

	virtual bool IsEnd() const;	// シーンが終了したかどうかを返す

protected:
	void set_Step( int step_ );	// 処理内容の切り替え

protected:
	int		m_Step;		// 処理内容を管理する変数
};

#endif // #ifndef SCENE_BASE_H
