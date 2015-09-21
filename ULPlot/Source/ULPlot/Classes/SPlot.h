// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SlateBasics.h"
#include "SLeafWidget.h"
/**
 * 
 */
class ULPLOT_API SPlot : public SLeafWidget
{

public:
	SLATE_BEGIN_ARGS(SPlot)
		: _Image(FCoreStyle::Get().GetDefaultBrush())
		, _ColorAndOpacity(FLinearColor::White)
		, _PlotMinX(0.0f)
		, _PlotMaxX(100.0f)
		, _PlotMinY(0.0f)
		, _PlotMaxY(100.0f)
		, _PlotOriginPos(FVector2D(20.0f,500.0f))
		, _PlotSize(FVector2D(500.0f,500.0f))
		, _PlotRow(4)
		, _PlotColumn(4)
		, _PlotRowInner(2)
		, _PlotColumnInner(2)
		, _PlotMainLineColor(FLinearColor::Red)
		, _PlotSublineColor(FLinearColor::Blue)
		, _PlotLabelColor(FLinearColor::Red)
		, _PlotLabelFontInfo()
		, _PlotDigitWidth(6.0f)
		, _PlotDigitHeight(8.0f)
		, _PlotLabelXOffset(8.0f)
		, _PlotLabelYOffset(6.0f)
		, _PlotPoints1(TArray<FVector2D>())
		, _PlotLineColor1(FLinearColor::Red)
		, _OnMouseButtonDown()
	{}

		/** Image resource */
		SLATE_ATTRIBUTE(const FSlateBrush*, Image)

		/** Color and opacity */
		SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity)

		/** Min X Value */
		SLATE_ATTRIBUTE(float,PlotMinX)

		/** Max X Value*/
		SLATE_ATTRIBUTE(float,PlotMaxX)

		/*Min Y Value*/
		SLATE_ATTRIBUTE(float,PlotMinY)
		
		/* Max Y Value */
		SLATE_ATTRIBUTE(float,PlotMaxY)
		
		/* Origin Position */
		SLATE_ATTRIBUTE(FVector2D,PlotOriginPos)

		/* Size */
		SLATE_ATTRIBUTE(FVector2D,PlotSize)
		
		/** Grid Rows */
		SLATE_ATTRIBUTE(int32,PlotRow)

		/** Grid Collums */
		SLATE_ATTRIBUTE(int32,PlotColumn)


		SLATE_ATTRIBUTE(int32,PlotRowInner)


		SLATE_ATTRIBUTE(int32,PlotColumnInner)


		SLATE_ATTRIBUTE(FLinearColor,PlotMainLineColor)


		SLATE_ATTRIBUTE(FLinearColor,PlotSublineColor)


		SLATE_ATTRIBUTE(FLinearColor,PlotLabelColor)


		SLATE_ATTRIBUTE(TAttribute<FSlateFontInfo>, PlotLabelFontInfo)


		SLATE_ATTRIBUTE(float, PlotDigitWidth)

		SLATE_ATTRIBUTE(float, PlotDigitHeight)
		
		SLATE_ATTRIBUTE(float, PlotLabelXOffset)
		
		SLATE_ATTRIBUTE(float, PlotLabelYOffset)

		SLATE_ATTRIBUTE(TArray<FVector2D>, PlotPoints1)

		SLATE_ATTRIBUTE(FLinearColor, PlotLineColor1)

		/** Invoked when the mouse is pressed in the widget. */
		SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown)

		SLATE_END_ARGS()

		/**
		* Construct this widget
		*
		* @param	InArgs	The declaration data for this widget
		*/
		void Construct(const FArguments& InArgs);

public:

	/** See the ColorAndOpacity attribute */
	void SetColorAndOpacity(const TAttribute<FSlateColor>& InColorAndOpacity);

	/** See the ColorAndOpacity attribute */
	void SetColorAndOpacity(FLinearColor InColorAndOpacity);

	/** See the Image attribute */
	void SetImage(TAttribute<const FSlateBrush*> InImage);

	/** Set the Plot Axis attribute */
	void SetPlotAxis(float InPlotMinX,float InPlotMaxX,float InPlotMinY,float InPlotMaxY);

	/** Set the Plot rect area */
	void SetPlotRect(FVector2D OriginPos, FVector2D size);

	/** Set the Plot Grid attribute */
	void SetPlotGrids(int32 Row, int32 Column, int32 RowInner, int32 ColumnInner, FLinearColor InPlotMainlineColor, FLinearColor InPlotSublineColor);

	/** Set the Plot Label attributes */
	void SetPlotLabels(FSlateFontInfo InPlotLabelFontInfo, FLinearColor InPlotLabelColor);

	void SetPlotLabelPosition(float InPlotDigitWidth, float InPlotDigitHeight, float InPlotLabelXOffset, float InPlotLabelYOffset);

	void SetPlotPoints(TArray<FVector2D> Points, FLinearColor LineColor, int LineIndex = 1);

	/** See OnMouseButtonDown event */
	void SetOnMouseButtonDown(FPointerEventHandler EventHandler);


	void PlotDrawLine(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
		FVector2D PositionA, FVector2D PositionB, FLinearColor Tint, bool bAntiAlias = true) const;

	void PlotDrawText(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled, 
		const FString& InString, FVector2D Position, FSlateFontInfo FontInfo, FLinearColor Tint) const;


	void DrawGrid(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
		float MinX,
		float MaxX,
		float MinY,
		float MaxY,
		FVector2D OriginPos,
		FVector2D Size,
		int32 Row,
		int32 Column,
		int32 RowInner,
		int32 ColumnInner,
		FLinearColor MainLineColor,
		FLinearColor SublineColor,
		FLinearColor LabelColor,
		FSlateFontInfo LabelFontInfofloat,
		float DigitWidth,
		float DigitHeight,
		float LabelXOffset,
		float LabelYOffset)const;

	void DrawPoints(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
		float MinX,
		float MaxX,
		float MinY,
		float MaxY,
		FVector2D OriginPos,
		FVector2D Size,
		TArray<FVector2D> Points,
		FLinearColor LineColor)const;


public:

	// SWidget overrides

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FVector2D ComputeDesiredSize(float) const override;

protected:

	/** The FName of the image resource to show */
	TAttribute< const FSlateBrush* > Image;

	/** Color and opacity scale for this image */
	TAttribute<FSlateColor> ColorAndOpacity;

	/** Invoked when the mouse is pressed in the image */
	FPointerEventHandler OnMouseButtonDownHandler;




	/** Min X Value */
	TAttribute<float> PlotMinX;

		/** Max X Value*/
	TAttribute<float> PlotMaxX;

		/*Min Y Value*/
	TAttribute<float>  PlotMinY;

		/* Max Y Value */
	TAttribute<float> PlotMaxY;

		/* Origin Position */
	TAttribute<FVector2D> PlotOriginPos;

		/* Size */
	TAttribute<FVector2D> PlotSize;

		/** Grid Rows */
	TAttribute<int32> PlotRow;

		/** Grid Collums */
	TAttribute<int32>  PlotColumn;


	TAttribute<int32>  PlotRowInner;


	TAttribute<int32> PlotColumnInner;

	TAttribute<FLinearColor> PlotMainLineColor;


	TAttribute<FLinearColor> PlotSublineColor;


	TAttribute<FLinearColor> PlotLabelColor;


	TAttribute<FSlateFontInfo> PlotLabelFontInfo;


	TAttribute<float> PlotDigitWidth;

	TAttribute<float> PlotDigitHeight;

	TAttribute<float> PlotLabelXOffset;

	TAttribute<float> PlotLabelYOffset;

	TAttribute<TArray<FVector2D>> PlotPoints1;

	TAttribute<FLinearColor> PlotLineColor1;

};
