
/*
 * Copyright 2020-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/**************************************
 * dedActStart.cpp
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.cpp.tt>
 **************************************/


#include "actionTable.h"
#include "actionHandlers/actionHandlers.h"
#include "mmeSmDefs.h"
#include "utils/mmeStatesUtils.h"
#include "utils/mmeTimerTypes.h"

#include "mmeStates/dedActStart.h"	
#include "mmeStates/dedActWfBearerAndSessionSetup.h"

using namespace mme;
using namespace SM;

/******************************************************************************
* Constructor
******************************************************************************/
DedActStart::DedActStart():State(ded_act_start)
{
        stateEntryAction = &MmeStatesUtils::on_state_entry;
        stateExitAction = &MmeStatesUtils::on_state_exit;
        eventValidator = &MmeStatesUtils::validate_event;
}

/******************************************************************************
* Destructor
******************************************************************************/
DedActStart::~DedActStart()
{
}

/******************************************************************************
* creates and returns static instance
******************************************************************************/
DedActStart* DedActStart::Instance()
{
        static DedActStart state;
        return &state;
}

/******************************************************************************
* initializes eventToActionsMap
******************************************************************************/
void DedActStart::initialize()
{
        {
                ActionTable actionTable;
                actionTable.setNextState(DedActWfBearerAndSessionSetup::Instance());
                eventToActionsMap.insert(pair<uint16_t, ActionTable>(GW_INIT_DED_BEARER_AND_SESSION_SETUP, actionTable));
        }
}