/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod PySMod Extension
 * Copyright (C) 2023 Dartz8901.  All rights reserved.
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

PySModExt g_PySModExt;		/**< Global singleton for extension's main interface */
SMEXT_LINK(&g_PySModExt);

CPySMod *g_pPySMod = new CPySMod;

void OnGameFrame(bool simulating);


bool PySModExt::SDK_OnLoad(char* error, size_t maxlength, bool late)
{
    g_pShareSys->RegisterLibrary(myself, "PySMod");

    playerhelpers->AddClientListener(this);      // IClientListener
    g_pSM->AddGameFrameHook(OnGameFrame);        // ISourceMod

    PyImport_AppendInittab("sourcemod", &PyInit_sourcemod);
    PyImport_AppendInittab("sourcemod.console", &PyInit_console);
    PyImport_AppendInittab("sourcemod.files", &PyInit_files);
    PyImport_AppendInittab("sourcemod.logging", &PyInit_logging);

    g_pPySMod->Initialize();
    if (!g_pPySMod->IsRunning())
    {
        return false;
    }

    return true;
}

void PySModExt::SDK_OnUnload()
{
    delete g_pPySMod;
    g_pPySMod = NULL;

    playerhelpers->RemoveClientListener(this);  // IClientListener
    g_pSM->RemoveGameFrameHook(OnGameFrame);    // ISourceMod
}

bool PySModExt::QueryRunning(char* error, size_t maxlength)
{
    return true;
}

void PySModExt::OnClientPutInServer(int client)  // declared in IClientListener
{
    if (g_pPySMod->IsRunning())
    {
        g_pPySMod->GetPluginManager()->Call_OnClientPutInServer(client);
    }
}

void PySModExt::OnEntityCreated(CBaseEntity* pEntity, const char* classname)
{
    if (g_pPySMod->IsRunning())
    {
        g_pPySMod->GetPluginManager()->Call_OnEntityCreated(pEntity, classname);
    }
}

void PySModExt::OnEntityDestroyed(CBaseEntity* pEntity)
{
    if (g_pPySMod->IsRunning())
    {
        g_pPySMod->GetPluginManager()->Call_OnEntityDestroyed(pEntity);
    }
}

void OnGameFrame(bool simulating)
{
    /*if (!simulating)
        return;*/

    if (g_pPySMod->IsRunning())
    {
        g_pPySMod->GetPluginManager()->Call_OnGameFrame();
    }
}
