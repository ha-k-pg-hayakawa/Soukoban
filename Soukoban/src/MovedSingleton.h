#ifndef MOVED_SINGLETON
#define MOVED_SINGLETON

class MovedSingleton
{
public:
	// インスタンスを取得するためのゲッター
	static MovedSingleton* Instance()
	{
		// この変数がこのクラスの唯一のインスタンス
		static MovedSingleton instance;

		return &instance;
	}

	void SetMoved(int value)
	{
		m_Moved = value;
	}
	int GetMoved()
	{
		return m_Moved;
	}

private:
	// インスタンス化を防ぐための処理
	MovedSingleton() 
	{
		m_Moved = 0;
	}

	int m_Moved;
};

#endif // !MOVED_SINGLETON

