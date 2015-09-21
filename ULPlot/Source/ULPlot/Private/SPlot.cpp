// Fill out your copyright notice in the Description page of Project Settings.

#include "ULPlotPch.h"
#include "SPlot.h"






/**
* Construct this widget
*
* @param	InArgs	The declaration data for this widget
*/
void SPlot::Construct(const SPlot::FArguments& InArgs)
{
	Image = InArgs._Image;
	ColorAndOpacity = InArgs._ColorAndOpacity;
	OnMouseButtonDownHandler = InArgs._OnMouseButtonDown;

	PlotMinX = InArgs._PlotMinX;
	PlotMaxX = InArgs._PlotMaxX;
	PlotMinY = InArgs._PlotMinY;
	PlotMaxY = InArgs._PlotMaxY;
	PlotOriginPos = InArgs._PlotOriginPos;
	PlotSize = InArgs._PlotSize;
	PlotRow = InArgs._PlotRow;
	PlotColumn = InArgs._PlotColumn;
	PlotRowInner = InArgs._PlotRowInner;
	PlotColumnInner = InArgs._PlotColumnInner;
	PlotMainLineColor = InArgs._PlotMainLineColor;
	PlotSublineColor = InArgs._PlotSublineColor;
	PlotLabelColor = InArgs._PlotLabelColor;
	PlotLabelFontInfo = InArgs._PlotLabelFontInfo.Get().Get();
	PlotDigitWidth = InArgs._PlotDigitWidth;
	PlotDigitHeight = InArgs._PlotDigitHeight;
	PlotLabelXOffset = InArgs._PlotLabelXOffset;
	PlotLabelYOffset = InArgs._PlotLabelYOffset;
	PlotPoints1 = InArgs._PlotPoints1;
	PlotLineColor1 = InArgs._PlotLineColor1;
}


int32 SPlot::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FSlateBrush* ImageBrush = Image.Get();

	if ((ImageBrush != nullptr) && (ImageBrush->DrawAs != ESlateBrushDrawType::NoDrawType))
	{
		const bool bIsEnabled = ShouldBeEnabled(bParentEnabled);
		const uint32 DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		const FLinearColor FinalColorAndOpacity(InWidgetStyle.GetColorAndOpacityTint() * ColorAndOpacity.Get().GetColor(InWidgetStyle) * ImageBrush->GetTint(InWidgetStyle));

		FSlateDrawElement::MakeBox(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), ImageBrush, MyClippingRect, DrawEffects, FinalColorAndOpacity);

		DrawGrid(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId+1, InWidgetStyle, bParentEnabled,
			PlotMinX.Get(), PlotMaxX.Get(), PlotMinY.Get(), PlotMaxY.Get(), PlotOriginPos.Get(), PlotSize.Get(),
			PlotRow.Get(), PlotColumn.Get(), PlotRowInner.Get(), PlotColumnInner.Get(),
			PlotMainLineColor.Get(), PlotSublineColor.Get(), PlotLabelColor.Get(), PlotLabelFontInfo.Get(),
			PlotDigitWidth.Get(),PlotDigitHeight.Get(),PlotLabelXOffset.Get(),PlotLabelYOffset.Get());

		// Draw line
		// TODO: To Allow Scattering
		if (PlotPoints1.Get().Num() >= 2){
		
			DrawPoints(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId + 2, InWidgetStyle, bParentEnabled,
				PlotMinX.Get(), PlotMaxX.Get(), PlotMinY.Get(), PlotMaxY.Get(), PlotOriginPos.Get(), PlotSize.Get(), PlotPoints1.Get(), PlotLineColor1.Get());
		
		}
		//FSlateDrawElement::MakeLines()
	}

	return LayerId;
}

/**
* The system calls this method to notify the widget that a mouse button was pressed within it. This event is bubbled.
*
* @param MyGeometry The Geometry of the widget receiving the event
* @param MouseEvent Information about the input event
*
* @return Whether the event was handled along with possible requests for the system to take action.
*/
FReply SPlot::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (OnMouseButtonDownHandler.IsBound())
	{
		// If a handler is assigned, call it.
		return OnMouseButtonDownHandler.Execute(MyGeometry, MouseEvent);
	}
	else
	{
		// otherwise the event is unhandled.
		return FReply::Unhandled();
	}
}

/**
* An Image's desired size is whatever the image looks best as. This is decided on a case by case basis via the Width and Height properties.
*/
FVector2D SPlot::ComputeDesiredSize(float) const
{
	const FSlateBrush* ImageBrush = Image.Get();
	if (ImageBrush != nullptr)
	{
		return ImageBrush->ImageSize;
	}
	return FVector2D::ZeroVector;
}

void SPlot::SetColorAndOpacity(const TAttribute<FSlateColor>& InColorAndOpacity)
{
	if (!ColorAndOpacity.IdenticalTo(InColorAndOpacity))
	{
		ColorAndOpacity = InColorAndOpacity;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SPlot::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	if (ColorAndOpacity.IsBound() || ColorAndOpacity.Get() != InColorAndOpacity)
	{
		ColorAndOpacity = InColorAndOpacity;
		Invalidate(EInvalidateWidget::Layout);
	}
}

void SPlot::SetImage(TAttribute<const FSlateBrush*> InImage)
{
	Image = InImage;
	Invalidate(EInvalidateWidget::Layout);
}


/** Set the Plot Axis attribute */
void SPlot::SetPlotAxis(float InPlotMinX, float InPlotMaxX, float InPlotMinY, float InPlotMaxY)
{
	PlotMinX = InPlotMinX;
	PlotMaxX = InPlotMaxX;
	PlotMinY = InPlotMinY;
	PlotMaxY = InPlotMaxY;
	Invalidate(EInvalidateWidget::Layout);

}


/** Set the Plot rect area */
void SPlot::SetPlotRect(FVector2D OriginPos, FVector2D size)
{
	PlotOriginPos = OriginPos;
	PlotSize = size;
	Invalidate(EInvalidateWidget::Layout);
}


/** Set the Plot Grid attribute */
void SPlot::SetPlotGrids(int32 Row, int32 Column, int32 RowInner, int32 ColumnInner, FLinearColor InPlotMainlineColor, FLinearColor InPlotSublineColor)
{
	PlotRow = Row;
	PlotColumn = Column;
	PlotRowInner = RowInner;
	PlotColumnInner = ColumnInner;
	PlotMainLineColor = InPlotMainlineColor;
	PlotSublineColor = InPlotSublineColor;
	Invalidate(EInvalidateWidget::Layout);
}


/** Set the Plot Label attributes */
void SPlot::SetPlotLabels(FSlateFontInfo InPlotLabelFontInfo, FLinearColor InPlotLabelColor){

	PlotLabelFontInfo = InPlotLabelFontInfo;
	PlotLabelColor = InPlotLabelColor;
	Invalidate(EInvalidateWidget::Layout);
}

void SPlot::SetPlotLabelPosition(float InPlotDigitWidth, float InPlotDigitHeight, float InPlotLabelXOffset, float InPlotLabelYOffset)
{
	PlotDigitWidth = InPlotDigitWidth;
	PlotDigitHeight = InPlotDigitHeight;
	PlotLabelXOffset = InPlotLabelXOffset;
	PlotLabelYOffset = InPlotLabelYOffset;
	Invalidate(EInvalidateWidget::Layout);
}

void SPlot::SetPlotPoints(TArray<FVector2D> Points, FLinearColor LineColor, int LineIndex){
	switch (LineIndex){
	case 1:
		PlotPoints1 = Points;
		PlotLineColor1 = LineColor;
		Invalidate(EInvalidateWidget::Layout);
		break;
	default:
		break;
	}

}

void SPlot::SetOnMouseButtonDown(FPointerEventHandler EventHandler)
{
	OnMouseButtonDownHandler = EventHandler;
}

void SPlot::PlotDrawLine(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
	FVector2D PositionA, FVector2D PositionB, FLinearColor Tint, bool bAntiAlias)const{

	TArray<FVector2D> points = TArray<FVector2D>();
	points.Empty();
	points.Add(PositionA);
	points.Add(PositionB);
	FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), points, MyClippingRect, ESlateDrawEffect::None, Tint, bAntiAlias);

}


void SPlot::PlotDrawText(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
	const FString& InString, FVector2D Position, FSlateFontInfo FontInfo, FLinearColor Tint) const{

	FSlateDrawElement::MakeText(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToOffsetPaintGeometry(Position),
		InString,
		FontInfo,
		MyClippingRect,
		ESlateDrawEffect::None,
		Tint);
}



void SPlot::DrawGrid(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
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
	FSlateFontInfo LabelFontInfo,
	float DigitWidth,
	float DigitHeight,
	float LabelXOffset,
	float LabelYOffset)const{



	float w_digit = DigitWidth;//length of each digit
	float h_digit = DigitHeight;// height of each digit
	float offsetx = LabelXOffset;
	float offsety = LabelYOffset;

	// Calculate Basic Parameters
	float sx = OriginPos.X;
	float width = Size.X;
	float height = Size.Y;
	float sy = OriginPos.Y - height;
	float ex = sx + width;
	float ey = OriginPos.Y;

	float dx = width / Column;
	float dy = height / Row;
	float _dx = dx / ColumnInner;
	float _dy = dy / RowInner;



	float dvx = (MaxX - MinX) / Column;
	float dvy = (MaxY - MinY) / Row;

	//Horizontal Lines
	for (int32 i = 0; i <= Row; i++){
		//Draw From Upper
		float ly = sy + i*dy;
		FVector2D p1 = FVector2D(sx, ly);
		FVector2D p2 = FVector2D(ex, ly);


		PlotDrawLine(Args,AllottedGeometry,MyClippingRect,OutDrawElements,LayerId,InWidgetStyle,bParentEnabled, p1, p2, MainLineColor, true);

		FString label = FString::SanitizeFloat(MaxY - i*dvy); // top to down => max to min
		float w = label.Len()*w_digit;
		float h = h_digit;
		//Draw Y Value Labels
		PlotDrawText(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, label, FVector2D(sx - offsetx - w, ly - h / 2.0f), LabelFontInfo,LabelColor);
		//UWidgetBlueprintLibrary::DrawText(Context, label, FVector2D(sx, ly), LabelColor);
		if (i == Row){ break; }
		if (RowInner<2){ continue; }
		for (int32 j = 1; j < RowInner; j++){
			float _ly = ly + j*_dy;
			PlotDrawLine(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, FVector2D(sx, _ly), FVector2D(ex, _ly), SublineColor, true);
		}
	}

	//Vertical Lines
	for (int32 i = 0; i <= Column; i++){
		//Draw From Upper
		float lx = sx + i*dx;
		FVector2D p1 = FVector2D(lx, sy);
		FVector2D p2 = FVector2D(lx, ey);
		PlotDrawLine(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, p1, p2, MainLineColor, true);
		//Draw X Value Labels
		FString label = FString::SanitizeFloat(MinX + i*dvx);
		float w = label.Len()*w_digit;
		float h = h_digit;

		PlotDrawText(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, label, FVector2D(lx - w / 2.0, ey + offsety), LabelFontInfo, LabelColor);


		if (i == Column){ break; }
		if (ColumnInner < 2){ continue; }
		for (int32 j = 1; j < ColumnInner; j++){
			float _lx = lx + j*_dx;
			PlotDrawLine(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, FVector2D(_lx, sy), FVector2D(_lx, ey), SublineColor, true);
		}
	}

}


void SPlot::DrawPoints(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled,
	float MinX,
	float MaxX,
	float MinY,
	float MaxY,
	FVector2D OriginPos,
	FVector2D Size,
	TArray<FVector2D> Points,
	FLinearColor LineColor)const{


	// Draw DataPoints

	// Calculate Basic Parameters
	float dxValue = MaxX - MinX;
	float dyValue = MaxY - MinY;

	float dxPos = Size.X;
	float dyPos = Size.Y;


	if (!(dxValue&&dyValue)){ return; }


	// remapping the values to the positions
	for (int32 i = 0; i < Points.Num()-1; i++){
		float rx = dxPos / dxValue;
		float ry = dyPos / dyValue;
		float x1 = (Points[i].X - MinX)*rx + OriginPos.X;
		float y1 = OriginPos.Y - (Points[i].Y - MinY)*ry;

		float x2 = (Points[i+1].X - MinX)*rx + OriginPos.X;
		float y2 = OriginPos.Y - (Points[i+1].Y - MinY)*ry;

		PlotDrawLine(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled, FVector2D(x1, y1), FVector2D(x2, y2), LineColor, true);

	}

	


}