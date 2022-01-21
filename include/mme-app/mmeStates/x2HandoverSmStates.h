

 /*
 * Copyright 2021-present Infosys Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
 /******************************************************
 * x2HandoverSmStates.h
 * This is an auto generated file.
 * Please do not edit this file.
 * All edits to be made through template source file
 * <TOP-DIR/scripts/SMCodeGen/templates/stateMachineTmpls/state.h.tt>
 ******************************************************/
 #ifndef __X2_HANDOVER_SM__
 #define __X2_HANDOVER_SM__

 #include "state.h"

 namespace mme {
	class X2HoSmStart : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static X2HoSmStart* Instance();

			/****************************************
			* X2HoSmStart
			*    Destructor
			****************************************/
			~X2HoSmStart();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();

			/*****************************************
			* returns stateId
			*****************************************/
			uint16_t getStateId() const;

			/*****************************************
			* returns stateName
			*****************************************/
			const char* getStateName() const;

		protected:
			/****************************************
			* X2HoSmStart
			*    Protected constructor
			****************************************/
			X2HoSmStart();  
	};
	
	class X2HoSmWfMbResp : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static X2HoSmWfMbResp* Instance();

			/****************************************
			* X2HoSmWfMbResp
			*    Destructor
			****************************************/
			~X2HoSmWfMbResp();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();

			/*****************************************
			* returns stateId
			*****************************************/
			uint16_t getStateId() const;

			/*****************************************
			* returns stateName
			*****************************************/
			const char* getStateName() const;

		protected:
			/****************************************
			* X2HoSmWfMbResp
			*    Protected constructor
			****************************************/
			X2HoSmWfMbResp();  
	};
	
	class X2HoSmWfHoComplete : public SM::State
	{
		public:
			/******************************************
			* Instance 
			*    Creates static instance for the state
			*******************************************/
			static X2HoSmWfHoComplete* Instance();

			/****************************************
			* X2HoSmWfHoComplete
			*    Destructor
			****************************************/
			~X2HoSmWfHoComplete();			
			
			/******************************************
			* initialize
			*  Initializes action handlers for the state
			* and next state
			******************************************/
			void initialize();

			/*****************************************
			* returns stateId
			*****************************************/
			uint16_t getStateId() const;

			/*****************************************
			* returns stateName
			*****************************************/
			const char* getStateName() const;

		protected:
			/****************************************
			* X2HoSmWfHoComplete
			*    Protected constructor
			****************************************/
			X2HoSmWfHoComplete();  
	};
	
};
#endif // __X2_HANDOVER_SM__