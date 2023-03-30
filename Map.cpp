#include "Map.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "Pad.h"
#include <iostream>
#include <fstream>

namespace
{
	//マップチップ1つのサイズ
	constexpr int chip_size = 32;

	//チップの数
	constexpr int bg_num_x = Game::screen_width / chip_size;
	constexpr int bg_num_y = Game::screen_height / chip_size;

	//入出力ファイル名
	const char* const file_name = "bin/map.bin";

	//マップデータ
	constexpr int map_data[bg_num_y][bg_num_x] =
	{
		{0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};
}

Map::Map() :
	handle_(-1),
	graphWidth_(0),
	graphHeight_(0),
	cursorNo_(0),
	mapData_(bg_num_x* bg_num_y, 3),
	scrollX_(0),
	scrollY_(0)
{
}

Map::~Map()
{
}

void Map::Load()
{
	handle_ = LoadGraph("data/mapchip.png");
	GetGraphSize(handle_, &graphWidth_, &graphHeight_);
}

void Map::Unoload()
{
	DeleteGraph(handle_);
}

void Map::Update()
{
	int indexX = cursorNo_ % bg_num_x;
	int indexY = cursorNo_ / bg_num_y;

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		//指定したマップチップの変更
		if (mapData_[cursorNo_] < (ChipNum() - 1))
		{
			mapData_[cursorNo_]++;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		//指定したマップチップの変更
		if (mapData_[cursorNo_] > 0)
		{
			mapData_[cursorNo_]--;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_3))
	{
		//ファイルの出力
	//	outputData();
		ReadData();
	}
#if 0
	if (Pad::isTrigger(PAD_INPUT_UP))
	{
		if (indexY > 0)
		{
			m_cursorNo -= kBgNumX;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		if (indexY < (kBgNumY - 1))
		{
			m_cursorNo += kBgNumX;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		if (indexY > 0)
		{
			m_cursorNo--;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		if (indexX < (kBgNumX - 1))
		{
			m_cursorNo++;
		}
	}
#else
	if (Pad::isPress(PAD_INPUT_UP))
	{
		scrollY_ += 8;
		if (scrollY_ > Game::screen_height)
		{
			scrollY_ -= Game::screen_height;
		}
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		scrollY_ -= 8;
		if (scrollY_ < -Game::screen_height)
		{
			scrollY_ += Game::screen_height;
		}
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		scrollX_ += 8;
		if (scrollX_ > Game::screen_width)
		{
			scrollX_ -= Game::screen_width;
		}
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		scrollX_ -= 8;
		if (scrollX_ < -Game::screen_width)
		{
			scrollX_ += Game::screen_width;
		}
	}
#endif
}

void Map::Draw()
{
	//m_scrollX > 0		右にずれている
	//m_scrollX < 0		左にずれている
	//m_scrollY > 0		下にずれている
	//m_scrollY > 0		上にずれている
#if false
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			int offsetX = x * Game::kScreenWidth + m_scrollX;
			int offsetY = y * Game::kScreenHeight + m_scrollY;
			drawMap(offsetX, offsetY);
		}
	}
#else
	int offsetX = scrollX_;
	if (offsetX > 0)	offsetX -= Game::screen_width;
	int offsetY = scrollY_;
	if (offsetY > 0)	offsetY -= Game::screen_height;

	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			DrawMap(offsetX + x * Game::screen_width, offsetY + y * Game::screen_height);
		}
	}
#endif

	DrawCursor();
}

void Map::DrawCursor()
{
	int indexX = cursorNo_ % bg_num_x;
	int indexY = cursorNo_ / bg_num_x;

	int graphX = indexX * chip_size;
	int graphY = indexY * chip_size;

	DrawBox(graphX, graphY, graphX + chip_size, graphY + chip_size, GetColor(255, 0, 0), false);
}

void Map::DrawMap(int offsetX, int offsetY)
{
	for (int x = 0; x < bg_num_x; x++)
	{
		for (int y = 0; y < bg_num_y; y++)
		{
			const int chipNo = mapData_[y * bg_num_x + x];
			assert(chipNo >= 0);
			assert(chipNo < ChipNum());
			int graphX = (chipNo % ChipNumX()) * chip_size;
			int graphY = (chipNo / ChipNumX()) * chip_size;

			DrawRectGraph(x * chip_size + offsetX, y * chip_size + offsetY,
				graphX, graphY, chip_size, chip_size,
				handle_, true, false);
		}
	}
}

int Map::ChipNumX()
{
	return (graphWidth_ / chip_size);
}

int Map::ChipNumY()
{
	return (graphHeight_ / chip_size);
}

int Map::ChipNum()
{
	return (ChipNumX() * ChipNumY());
}

void Map::OutputData()
{
	std::ofstream ofs(file_name, std::ios::binary);

	//ファイルの読み込みに失敗
	if (!ofs)
	{
		return;
	}
	ofs.write(reinterpret_cast<char*>(mapData_.data()), sizeof(int) * bg_num_x * bg_num_y);

	ofs.close();
}
void Map::ReadData()
{
	std::ifstream ifs(file_name, std::ios::binary);

	//ファイルの読み込みに失敗
	if (!ifs)
	{
		return;
	}
	ifs.read(reinterpret_cast<char*>(mapData_.data()), sizeof(int) * bg_num_x * bg_num_y);

	ifs.close();
}