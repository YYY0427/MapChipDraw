#pragma once
#include <vector>

class Map
{
public:
	Map();
	virtual ~Map();

	// �O���t�B�b�N�f�[�^�̃��[�h�A�A�����[�h
	void Load();
	void Unoload();

	// �X�V
	void Update();

	// �`��
	void Draw();

private:
	// �}�b�v�`�b�v�ҏW�p�J�[�\���̕\��
	void DrawCursor();

	// �}�b�v�`�b�v�̕`��
	void DrawMap(int offsetX, int offsetY);

	// �}�b�v�`�b�v�̐����擾����
	int ChipNumX();
	int ChipNumY();
	int ChipNum();

	// �}�b�v�f�[�^�̓��o��
	void OutputData();		// �}�b�v�̃f�[�^���o�͂���
	void ReadData();		// �}�b�v�̃f�[�^��ǂݍ���

private:
	// �O���t�B�b�N�f�[�^�̃n���h��
	int handle_;

	// �O���t�B�b�N�̃f�[�^
	int graphWidth_;
	int graphHeight_;

	// �}�b�v�`�b�v�ҏW�p�f�[�^
	int cursorNo_;
	std::vector<int> mapData_;

	// �X�N���[������
	int scrollX_;
	int scrollY_;
};