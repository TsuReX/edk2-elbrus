
[Defines]
  PLATFORM_NAME                       = TestCbtPldPkg
  PLATFORM_GUID                       = F71608AB-D63D-4491-B744-A99998C8CD96
  PLATFORM_VERSION                    = 0.1
  DSC_SPECIFICATION                   = 0x00010005
  SUPPORTED_ARCHITECTURES             = EL64
  BUILD_TARGETS                       = DEBUG|RELEASE
  SKUID_IDENTIFIER                    = DEFAULT
  OUTPUT_DIRECTORY                    = Build/TestCbtPldPkg
  FLASH_DEFINITION                    = TestCbtPldPkg/TestCbtPldPkg.fdf

  DEFINE SECURE_BOOT_ENABLE      = FALSE
  DEFINE SOURCE_DEBUG_ENABLE     = FALSE


[BuildOptions]

[SkuIds]
	0|DEFAULT

[LibraryClasses]
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
#  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
#  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
#  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
#  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
#!if $(PCIE_BASE) == 0
#  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
#  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
#!else
#  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
#  PciExpressLib|MdePkg/Library/BasePciExpressLib/BasePciExpressLib.inf
#!endif
#  PciSegmentLib|MdePkg/Library/BasePciSegmentLibPci/BasePciSegmentLibPci.inf
#  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
#  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
#  CacheMaintenanceLib|MdePkg/Library/BaseCacheMaintenanceLib/BaseCacheMaintenanceLib.inf  
  
#[PcdsFeatureFlag]

#[PcdsFixedAtBuild]

#[PcdsPatchableInModule.common]

#[PcdsDynamicDefault]

[Components]

	TestCbtPldPkg/TestModule/TestModule.inf

#[PcdsFixedAtBuild]
 
[LibraryClasses]

