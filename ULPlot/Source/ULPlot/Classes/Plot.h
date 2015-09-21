// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "Runtime/UMG/Public/Components/Widget.h"
#include "SPlot.h"
#include "Plot.generated.h"

class USlateBrushAsset;

/**
* The image widget allows you to display a Slate Brush, or texture or material in the UI.
*
* ¡ñ No Children
*/
UCLASS()
class ULPLOT_API UPlot : public UWidget
{
	GENERATED_UCLASS_BODY()

public:

	/** Image to draw */
	UPROPERTY()
		USlateBrushAsset* Image_DEPRECATED;

	/** Image to draw */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateBrush Brush;

	/** A bindable delegate for the Image. */
	UPROPERTY()
		FGetSlateBrush BrushDelegate;

	/** Color and opacity */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (sRGB = "true"))
		FLinearColor ColorAndOpacity;

	/** A bindable delegate for the ColorAndOpacity. */
	UPROPERTY()
		FGetLinearColor ColorAndOpacityDelegate;


	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		float MinX=0.0f;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		float MaxX = 500.0f;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		float MinY = 0.0f;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		float MaxY = 500.0f;


	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		int32 Row;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		int32 Column;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		int32 RowInner;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		int32 ColumnInner;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FLinearColor MainlineColor;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FLinearColor SublineColor;


	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FVector2D OriginPositon;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FVector2D PlotSize;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FSlateFontInfo PlotFontInfo;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
	float DigitWidth;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
	float DigitHeight;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
	float LabelXOffset;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
	float LabelYOffset;
	

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		TArray<FVector2D> Points1;

	/**  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Plot)
		FLinearColor LineColor1;

public:

	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "True"))
		FOnPointerEvent OnMouseButtonDownEvent;

public:

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetColorAndOpacity(FLinearColor InColorAndOpacity);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetOpacity(float InOpacity);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrush(const FSlateBrush& InBrush);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromAsset(USlateBrushAsset* Asset);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromTexture(UTexture2D* Texture, bool bMatchSize = false);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		void SetBrushFromMaterial(UMaterialInterface* Material);

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Plot")
		void SetDataPoints(TArray<FVector2D> InDataPoint,FLinearColor LineColor,int32 Index);


	/**  */
	UFUNCTION(BlueprintCallable, Category = "Appearance")
		UMaterialInstanceDynamic* GetDynamicMaterial();

	// UWidget interface
	virtual void SynchronizeProperties() override;
	// End of UWidget interface

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

	// Begin UObject interface
	virtual void PostLoad() override;
	// End of UObject interface

#if WITH_EDITOR
	// UWidget interface
	virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	/** Translates the bound brush data and assigns it to the cached brush used by this widget. */
	const FSlateBrush* ConvertImage(TAttribute<FSlateBrush> InImageAsset) const;

	FReply HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent);

protected:
	TSharedPtr<SPlot> MyImage;
};