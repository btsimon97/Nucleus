/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2003-2018, Great Software Laboratory Pvt. Ltd.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "json_data.h"
#include "err_codes.h"
#include "log.h"
#include "s1ap_config.h"

static int get_mcc_mnc(char *plmn, uint16_t *mcc_i, uint16_t *mnc_i, uint16_t *mnc_digits);

void
init_parser(char *path)
{
	load_json(path);
}

int
parse_s1ap_conf(s1ap_config_t *config)
{
    config->rel_cap = 10;

	/*s1ap information*/
	config->mme_name = get_string_scalar("mme.name");
	if(NULL == config->mme_name) return -1;

	config->s1ap_local_ip = get_ip_scalar("s1ap.s1ap_local_addr");
	if(-1 == config->s1ap_local_ip) return -1;
	config->sctp_port = get_int_scalar("s1ap.sctp_port");
	if(-1 == config->sctp_port) return -1;

        /* TODO : should i get rid of this config (mme group id & mme code)  from s1-ap ? */
	config->mme_group_id = get_int_scalar("mme.group_id");
	if(-1 == config->mme_group_id) return -1;

	config->mme_code = get_int_scalar("mme.code");
	if(-1 == config->mme_code) return -1;

	config->logging = get_string_scalar((char *)("mme.logging"));
	if(NULL == config->logging) 
	{ 
		config->logging = (char *)calloc(1, 16);
		strncpy(config->logging, "debug", strlen("debug")+1);
	}
	set_logging_level(config->logging); 

	char *mp = getenv("MANAGED_BY_CONFIG_POD");
    if (mp == NULL || !strcmp(mp, "true")) {
	    uint16_t count=1;
	    while(1) {
	    	char name[100] = {'\0'};
	    	sprintf(name,"%s%d","mme.plmnlist.plmn",count);
	    	char *plmn = get_string_scalar(name);
	    	if(NULL == plmn) {
	    		// over
	    		break;
	    	}
	    	log_msg(LOG_INFO, "Parsed plmn %s ", plmn);
	    	uint16_t mcc_i, mnc_i;
	    	uint16_t mnc_digits=3;
            get_mcc_mnc(plmn, &mcc_i, &mnc_i, &mnc_digits);
	    	log_msg(LOG_INFO, "Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
	    	unsigned char mcc_dig_1 = mcc_i / 100; 
	    	unsigned char mcc_dig_2 = (mcc_i / 10) % 10; 
	    	unsigned char mcc_dig_3 = mcc_i % 10; 
	    	unsigned char mnc_dig_1; 
	    	unsigned char mnc_dig_2;
	    	unsigned char mnc_dig_3;
	    	if(mnc_digits == 2) // 01
	    	{
	    		mnc_dig_1 = 0x0F;
	    		mnc_dig_2 = mnc_i / 10;
	    	}
	    	else
	    	{
	    		mnc_dig_1 = mnc_i / 100;
	    		mnc_dig_2 = (mnc_i / 10) % 10; 
	    	}
	    	mnc_dig_3 = mnc_i % 10;
	    	/* these values used to compare s1 setup Request */
	    	config->plmns[count-1].idx[0] = (mcc_dig_2 << 4) | (mcc_dig_1);
	    	config->plmns[count-1].idx[1] = (mnc_dig_1 << 4) | (mcc_dig_3);
	    	config->plmns[count-1].idx[2] = (mnc_dig_3 << 4) | (mnc_dig_2);
	    	config->plmns[count-1].mnc_digits = mnc_digits;
	    	log_msg(LOG_INFO, "Configured plmn %x %x %x", config->plmns[count-1].idx[0], config->plmns[count-1].idx[1], config->plmns[count-1].idx[2]); 
	    	count++;
			free(plmn);
	    }
	    config->num_plmns = count - 1;
    }
	log_msg(LOG_ERROR,"Config parsing success ");
	return SUCCESS;
}

void 
update_mcc_mnc(s1ap_config_t *config, char **plmns, int num_plmns)
{
	uint16_t count=1;
    int index = 0;
	log_msg(LOG_INFO, "update plmns %d ", num_plmns);
    for(index = 0; index < num_plmns; index++) {
		char *plmn = plmns[index]; 
		log_msg(LOG_INFO, "Parsed plmn %s ", plmn);
		uint16_t mcc_i, mnc_i;
		uint16_t mnc_digits=3;
        get_mcc_mnc(plmn, &mcc_i, &mnc_i, &mnc_digits);
		log_msg(LOG_INFO, "Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
		unsigned char mcc_dig_1 = mcc_i / 100; 
		unsigned char mcc_dig_2 = (mcc_i / 10) % 10; 
		unsigned char mcc_dig_3 = mcc_i % 10; 
		unsigned char mnc_dig_1; 
		unsigned char mnc_dig_2;
		unsigned char mnc_dig_3;
		if(mnc_digits == 2) // 01
		{
			mnc_dig_1 = 0x0F;
			mnc_dig_2 = mnc_i / 10;
		}
		else
		{
			mnc_dig_1 = mnc_i / 100;
			mnc_dig_2 = (mnc_i / 10) % 10; 
		}
		mnc_dig_3 = mnc_i % 10;
		log_msg(LOG_INFO, "1 Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
		/* these values used to compare s1 setup Request */
		config->plmns[count-1].idx[0] = (mcc_dig_2 << 4) | (mcc_dig_1);
		log_msg(LOG_INFO, "2 Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
		config->plmns[count-1].idx[1] = (mnc_dig_1 << 4) | (mcc_dig_3);
		log_msg(LOG_INFO, "3 Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
		config->plmns[count-1].idx[2] = (mnc_dig_3 << 4) | (mnc_dig_2);
		log_msg(LOG_INFO, "4 Parsed plmn mcc - %d mnc - %d ", mcc_i, mnc_i);
		config->plmns[count-1].mnc_digits = mnc_digits;
		log_msg(LOG_INFO, "Configured plmn %x %x %x", config->plmns[count-1].idx[0], config->plmns[count-1].idx[1], config->plmns[count-1].idx[2]); 
		count++;
	}
	config->num_plmns = num_plmns;
    return;
}

/* plmn1: "mcc=315,mnc=010" */
static int
get_mcc_mnc(char *plmn, uint16_t *mcc_i, uint16_t *mnc_i, uint16_t *mnc_digits)
{
	char *token = ",";
	char *saved_comma=NULL;
	char *mcc = strtok_r(plmn, token, &saved_comma);
	char *mnc = strtok_r(NULL, token, &saved_comma);

	char *saved_e=NULL;
	char *token_e = "=";
	char *mcc_f = strtok_r(mcc, token_e, &saved_e);
	mcc_f = strtok_r(NULL, token_e, &saved_e);
	*mcc_i = atoi(mcc_f);

	saved_e=NULL;
	char *mnc_f = strtok_r(mnc, token_e, &saved_e);
	mnc_f = strtok_r(NULL, token_e, &saved_e);
    *mnc_digits = strlen(mnc_f);
	*mnc_i = atoi(mnc_f);
	return 0;
}

