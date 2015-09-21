// Fill out your copyright notice in the Description page of Project Settings.

#include "ULPlotPch.h"
#include "Plot.h"

#include "Slate/SlateBrushAsset.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// UPlot

UPlot::UPlot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ColorAndOpacity(FLinearColor::White)
{
}

void UPlot::PostLoad()
{
	Super::PostLoad();

	if (GetLinkerUE4Version() < VER_UE4_DEPRECATE_UMG_STYLE_ASSETS && Image_DEPRECATED != nullptr)
	{
		Brush = Image_DEPRECATED->Brush;
		Image_DEPRECATED = nullptr;
	}
}

void UPlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyImage.Reset();
}

TSharedRef<SWidget> UPlot::RebuildWidget()
{
	MyImage = SNew(SPlot);
	return MyImage.ToSharedRef();
}

void UPlot::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<FSlateColor> ColorAndOpacityBinding = OPTIONAL_BINDING(FSlateColor, ColorAndOpacity);
	TAttribute<const FSlateBrush*> ImageBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, Brush, const FSlateBrush*, ConvertImage);

	MyImage->SetImage(ImageBinding);
	MyImage->SetColorAndOpacity(ColorAndOpacityBinding);
	MyImage->SetOnMouseButtonDown(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonDown));

	MyImage->SetPlotAxis(MinX, MaxX, MinY, MaxY);
	MyImage->SetPlotGrids(Row, Column, RowInner, ColumnInner,MainlineColor,SublineColor);
	MyImage->SetPlotRect(OriginPositon, PlotSize);
	MyImage->SetPlotLabels(PlotFontInfo, MainlineColor);

	MyImage->SetPlotLabelPosition(DigitWidth, DigitHeight, LabelXOffset, LabelYOffset);

	MyImage->SetPlotPoints(Points1, LineColor1, 1);
}

void UPlot::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacity = InColorAndOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

void UPlot::SetOpacity(float InOpacity)
{
	ColorAndOpacity.A = InOpacity;
	if (MyImage.IsValid())
	{
		MyImage->SetColorAndOpacity(ColorAndOpacity);
	}
}

const FSlateBrush* UPlot::ConvertImage(TAttribute<FSlateBrush> InImageAsset) const
{
	UPlot* MutableThis = const_cast<UPlot*>(this);
	MutableThis->Brush = InImageAsset.Get();

	return &Brush;
}

void UPlot::SetBrush(const FSlateBrush& InBrush)
{
	Brush = InBrush;

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UPlot::SetBrushFromAsset(USlateBrushAsset* Asset)
{
	Brush = Asset ? Asset->Brush : FSlateBrush();

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UPlot::SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize)
{
	Brush.SetResourceObject(Texture);

	if (bMatchSize)
	{
		Brush.ImageSize.X = Texture->GetSizeX();
		Brush.ImageSize.Y = Texture->GetSizeY();
	}

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UPlot::SetBrushFromMaterial(UMaterialInterface* Material)
{
	Brush.SetResourceObject(Material);

	//TODO UMG Check if the material can be used with the UI

	if (MyImage.IsValid())
	{
		MyImage->SetImage(&Brush);
	}
}

void UPlot::SetDataPoints(TArray<FVector2D> InDataPoint, FLinearColor LineColor, int32 Index){
	switch (Index)
	{
	case 1:
		Points1 = InDataPoint;
		LineColor1 = LineColor;
		MyImage->SetPlotPoints(InDataPoint, LineColor, Index);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}

}

UMaterialInstanceDynamic* UPlot::GetDynamicMaterial()
{
	UMaterialInterface* Material = NULL;

	UObject* Resource = Brush.GetResourceObject();
	Material = Cast<UMaterialInterface>(Resource);

	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

		if (!DynamicMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
			Brush.SetResourceObject(DynamicMaterial);

			if (MyImage.IsValid())
			{
				MyImage->SetImage(&Brush);
			}
		}

		return DynamicMaterial;
	}

	//TODO UMG can we do something for textures?  General purpose dynamic material for them?

	return NULL;
}

FReply UPlot::HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if (OnMouseButtonDownEvent.IsBound())
	{
		return OnMouseButtonDownEvent.Execute(Geometry, MouseEvent).NativeReply;
	}

	return FReply::Unhandled();
}

#if WITH_EDITOR

const FSlateBrush* UPlot::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Image");
}

const FText UPlot::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}

#endif


/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE