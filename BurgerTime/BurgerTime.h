#pragma once
#include "Minigin.h"

//#if _DEBUG
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif

//#include <Minigin.h>

class BurgerTime :
    public dae::Minigin
{
public:
    void LoadGame() override;
};

