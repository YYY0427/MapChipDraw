#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}


	virtual void Init() {}
	virtual void End()	{}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// �t�F�[�h�֘A
	void UpdateFade();
	void DrawFade() const;

	bool IsFadingIn() const;	// �t�F�[�h�C����
	bool IsFadingOut() const;	// �t�F�[�h�A�E�g��
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }	// �t�F�[�h�C��or�A�E�g��

	void StartFadeOut();	// �t�F�[�h�A�E�g�J�n

private:
	// �t�F�[�h�֘A����
	int fadeColor_;
	int fadeBright_;
	int fadeSpeed_;
};