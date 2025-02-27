#pragma once

#include <random>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <limits>
#include <codecvt>
#include <functional>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Includes/json.hpp"
using json = nlohmann::json;

#include "GameDefine.h"
#include "Defines.h"
#include "JsonDefines.h"
#include "Variables.h"
#include "DebugBox.h"
#include "HitBox.h"
#include "Utils.h"
#include "Singleton.h"
#include "SaveDataMgr.h"
#include "DataTable.h"
#include "StringTable.h"
#include "StageTable.h"
#include "BulletTable.h"
#include "DataTableMgr.h"
#include "Framework.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Animator.h"
#include "GameObject.h"
#include "SpriteGo.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjectPool.h"
#include "SoundMgr.h"