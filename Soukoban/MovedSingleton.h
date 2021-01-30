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
		Moved = value;
	}
	int GetMoved()
	{
		return Moved;
	}

private:
	// インスタンス化を防ぐための処理
	MovedSingleton() {}

	int Moved;
};

#endif // !MOVED_SINGLETON

