//==============================================
// 绘制旋转七彩动画
//==============================================

#pragma once
#include <gdiplus.h>

// CRotateAnimation
class CRotateAnimation
{
public:
	CRotateAnimation();
	virtual ~CRotateAnimation();
public:
	//设置动画类型
	void SetType(int nType,int nMarginAngle=0);
private:
	//初始化动画设置
	void InitAnimation();
	//播放下一帧
	void PlayNext(HDC hDestDC=NULL);
	//绘制动画
	void Draw(HDC hDestDC);
	//绘制圆饼
	void DrawPie(HDC hDC);
	//复制缓存DC
	void BitBlt(HDC hDestDC);
	//释放资源
	void Release();
private:
	typedef struct tagAnimationItem
	{
		COLORREF clrOut;//外圈颜色
		COLORREF clrIn;//内圈颜色
	} AnimationItem, *PAnimationItem;
private:
	int m_nWidth;//窗口宽度
	int m_nHeight;//窗口高度
	Gdiplus::Rect m_Rect;//圆形位置
	COLORREF m_ColorBack;//背景颜色
	AnimationItem m_ColorBasic;//基本颜色
	PAnimationItem m_pColorArray;//颜色数组
	PAnimationItem m_pAnimationArray;//动画小块数组
	int m_AnimationCount;//动画块数
	int m_AnimationIndex;//当前动画索引
	int m_AnimationType;//动画类型
	int m_MarginAngle;//空白区域角度
	int m_ItemSize;//色块高度
	HDC m_hCacheDC;//缓存DC
	HBITMAP m_hCacheBitmap;//缓存位图
	HBITMAP m_hCacheOldBitmap;
};


