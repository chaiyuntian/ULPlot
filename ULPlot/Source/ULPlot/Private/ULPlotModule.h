#pragma once


class ULPlotModule : public IModuleInterface
{
public:
	ULPlotModule();
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};