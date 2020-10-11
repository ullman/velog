/*
Copyright (C) 2020  "Philip J Freeman" <elektron@halo.nu>
License: GPL Version 3
*/

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "vedirect.h"

int init_suite(void)
{
	return 0;
}

int clean_suite(void)
{
	return 0;
}

void test__parse_block__checksum_validation(void) {
	ve_direct_block_t *b = NULL;

	char *test_block_bad_checksum =
		"\r\nChecksum\t\xff";

	char *test_block_good_checksum =
		"\r\nChecksum\t\xad";

	b = ve_direct_parse_block(test_block_bad_checksum);
	CU_ASSERT(b == NULL);

	b = ve_direct_parse_block(test_block_good_checksum);
	CU_ASSERT(b != NULL);

	ve_direct_free_block(b);
}

void test__parse_block__linked_list(void) {
	ve_direct_block_t *b = NULL;
	ve_direct_raw_fields_t *f;

	char *test_block =
		"\r\nA\t1"
		"\r\nB\t2"
		"\r\nC\t3"
		"\r\nChecksum\t\xf1";

	b = ve_direct_parse_block(test_block);
	f = b->raw_fields;
	CU_ASSERT_STRING_EQUAL(f->name, "A");
	CU_ASSERT_STRING_EQUAL(f->value, "1");
	f = f-> next;
	CU_ASSERT_STRING_EQUAL(f->name, "B");
	CU_ASSERT_STRING_EQUAL(f->value, "2");
	f = f-> next;
	CU_ASSERT_STRING_EQUAL(f->name, "C");
	CU_ASSERT_STRING_EQUAL(f->value, "3");
	f = f-> next;
	CU_ASSERT_STRING_EQUAL(f->name, "Checksum");
	CU_ASSERT_STRING_EQUAL(f->value, "\xf1");
	f = f-> next;
	CU_ASSERT(f == NULL);

	ve_direct_free_block(b);
}

void test__parse_block__mppt_001(void) {
	ve_direct_block_t *b = NULL;

	char *test_block =
		"\r\nPID\t0xA042"
		"\r\nFW\t150"
		"\r\nSER#\tHQ1909K249H"
		"\r\nV\t12440"
		"\r\nI\t0"
		"\r\nVPV\t0"
		"\r\nPPV\t0"
		"\r\nCS\t0"
		"\r\nMPPT\t0"
		"\r\nERR\t0"
		"\r\nLOAD\tOFF"
		"\r\nIL\t0"
		"\r\nH19\t559"
		"\r\nH20\t24"
		"\r\nH21\t84"
		"\r\nH22\t22"
		"\r\nH23\t67"
		"\r\nHSDS\t34"
		"\r\nChecksum\t\xc8";

	b = ve_direct_parse_block(test_block);
	CU_ASSERT_EQUAL(b->pid, 0xA042);
	CU_ASSERT_EQUAL(b->device_info->type, ve_direct_device_type_mppt);
	CU_ASSERT_STRING_EQUAL(b->device_info->name, "BlueSolar MPPT 75|15");
	ve_direct_free_block(b);
}

void test__parse_block__inverter_001(void) {
	ve_direct_block_t *b = NULL;

	char *test_block =
		"\r\nPID\t0xA279"
		"\r\nFW\t0121"
		"\r\nSER#\tHQ2017JGK6S"
		"\r\nMODE\t2"
		"\r\nCS\t9"
		"\r\nAC_OUT_V\t12003"
		"\r\nAC_OUT_I\t2"
		"\r\nV\t13308"
		"\r\nAR\t0"
		"\r\nWARN\t0"
		"\r\nOR\t0x00000000"
		"\r\nChecksum\t\x05";

	b = ve_direct_parse_block(test_block);
	CU_ASSERT_EQUAL(b->pid, 0xA279);
	CU_ASSERT_EQUAL(b->device_info->type, ve_direct_device_type_inverter);
	CU_ASSERT_STRING_EQUAL(b->device_info->name, "Phoenix Inverter 12V 1200VA 120V");
	ve_direct_free_block(b);
}

void test__parse_block__bmv_001(void) {
	ve_direct_block_t *b = NULL;

	char *test_block_pt_1 =
		"\r\nPID\t0xA381"
		"\r\nV\t13043"
		"\r\nT\t23"
		"\r\nI\t3856"
		"\r\nP\t50"
		"\r\nCE\t0"
		"\r\nSOC\t1000"
		"\r\nTTG\t-1"
		"\r\nAlarm\tOFF"
		"\r\nRelay\tOFF"
		"\r\nAR\t0"
		"\r\nBMV\t712 Smart"
		"\r\nFW\t0403"
		"\r\nChecksum\t\xb5";

	char *test_block_pt_2 =
		"\r\nH1\t-161154"
		"\r\nH2\t0"
		"\r\nH3\t0"
		"\r\nH4\t0"
		"\r\nH5\t0"
		"\r\nH6\t-979550"
		"\r\nH7\t29"
		"\r\nH8\t14371"
		"\r\nH9\t0"
		"\r\nH10\t1"
		"\r\nH11\t0"
		"\r\nH12\t0"
		"\r\nH15\t26"
		"\r\nH16\t9047"
		"\r\nH17\t1224"
		"\r\nH18\t1145"
		"\r\nChecksum\t\x01";


	b = ve_direct_parse_block(test_block_pt_1);
	CU_ASSERT_EQUAL(b->pid, 0xA381);
	ve_direct_free_block(b);

	b = ve_direct_parse_block(test_block_pt_2);
	CU_ASSERT_EQUAL(b->pid, NULL); // Second block has no PID
	CU_ASSERT_EQUAL(b->device_info, NULL); // and no device_info
	ve_direct_free_block(b);
}

int main (void)
{
	CU_pSuite suite1 = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	suite1 = CU_add_suite("VE.Direct_Test_Suite", init_suite, clean_suite);

	if (NULL == suite1) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_ADD_TEST(suite1, test__parse_block__checksum_validation))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_ADD_TEST(suite1, test__parse_block__linked_list))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_ADD_TEST(suite1, test__parse_block__mppt_001))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_ADD_TEST(suite1, test__parse_block__inverter_001))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_ADD_TEST(suite1, test__parse_block__bmv_001))) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();

	CU_cleanup_registry();

	return CU_get_error();
}
