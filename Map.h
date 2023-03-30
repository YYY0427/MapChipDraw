#pragma once
#include <vector>

class Map
{
public:
	Map();
	virtual ~Map();

	// グラフィックデータのロード、アンロード
	void Load();
	void Unoload();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// マップチップ編集用カーソルの表示
	void DrawCursor();

	// マップチップの描画
	void DrawMap(int offsetX, int offsetY);

	// マップチップの数を取得する
	int ChipNumX();
	int ChipNumY();
	int ChipNum();

	// マップデータの入出力
	void OutputData();		// マップのデータを出力する
	void ReadData();		// マップのデータを読み込む

private:
	// グラフィックデータのハンドル
	int handle_;

	// グラフィックのデータ
	int graphWidth_;
	int graphHeight_;

	// マップチップ編集用データ
	int cursorNo_;
	std::vector<int> mapData_;

	// スクロールする
	int scrollX_;
	int scrollY_;
};