#pragma once
#ifndef _SFXAPI_H_
#define _SFXAPI_H_

#ifndef _ENGINEAPI_H_
#include "console/engineAPI.h"
#endif

#ifndef _SFXENUMS_H_
#include "sfx/sfxEnums.h"
#endif

DECLARE_SCOPE(SFXAPI);

DefineEnumType(SFXChannel);
DefineEnumType(SFXDistanceModel);
DefineEnumType(SFXStatus);
DefineEnumType(SFXProviderType);

DefineConsoleType(TypeSFXChannel, SFXChannel)
DefineConsoleType(TypeSFXProviderType, SFXProviderType)
DefineConsoleType(TypeSFXStatus, SFXStatus)
DefineConsoleType(TypeSFXDistanceModel, SFXDistanceModel)

#endif // !_SFXAPI_H_
