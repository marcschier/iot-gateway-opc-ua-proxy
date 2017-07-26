// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#define UNIT_UNDER_TEST pal_scan_win
#include "util_ut.h"

//
// 1. Required mocks
//
#include "os.h"
#include "prx_types.h"
#include "prx_err.h"
#include "util_string.h"

// winsock2.h
MOCKABLE_FUNCTION(WSAAPI, int, closesocket,
    SOCKET, s);
// iphlpapi.h
MOCKABLE_FUNCTION(WINAPI, ULONG, GetAdaptersAddresses,
    ULONG, Family, ULONG, Flags, PVOID, Reserved, PIP_ADAPTER_ADDRESSES, AdapterAddresses,
    PULONG, SizePointer);
// netioapi.h
MOCKABLE_FUNCTION(WINAPI, NETIO_STATUS, GetIpNetTable2,
    ADDRESS_FAMILY, Family, PMIB_IPNET_TABLE2*, Table);
MOCKABLE_FUNCTION(WINAPI, void, FreeMibTable,
    PVOID, Memory);
// ioapiset.h
MOCKABLE_FUNCTION(WINAPI, BOOL, CancelIoEx,
    HANDLE, hFile, LPOVERLAPPED, lpOverlapped);
// Custom
MOCKABLE_FUNCTION(WINAPI, BOOL, HasOverlappedIoCompleted,
    LPOVERLAPPED, lpOverlapped);

//
// 2. Include unit under test
//
#undef ENABLE_MOCKS
#include "pal_scan.h"
#include "pal_types.h"
#define ENABLE_MOCKS
#include UNIT_C

// pal_types.h - platform independent
MOCKABLE_FUNCTION(, int32_t, pal_os_to_prx_socket_address,
    const struct sockaddr*, sa, socklen_t, sa_len, prx_socket_address_t*, prx_address);

//
// 3. Setup test suite
//
BEGIN_DECLARE_TEST_SUITE()
REGISTER_UMOCK_ALIAS_TYPE(ULONG, unsigned long);
REGISTER_UMOCK_ALIAS_TYPE(PULONG, void*);
REGISTER_UMOCK_ALIAS_TYPE(DWORD, unsigned int);
REGISTER_UMOCK_ALIAS_TYPE(LPDWORD, void*);
REGISTER_UMOCK_ALIAS_TYPE(HANDLE, void*);
REGISTER_UMOCK_ALIAS_TYPE(socklen_t, int);
REGISTER_UMOCK_ALIAS_TYPE(NETIO_STATUS, int);
REGISTER_UMOCK_ALIAS_TYPE(ADDRESS_FAMILY, int);
REGISTER_UMOCK_ALIAS_TYPE(LPOVERLAPPED_COMPLETION_ROUTINE, void*);
REGISTER_UMOCK_ALIAS_TYPE(LPOVERLAPPED, void*);
REGISTER_UMOCK_ALIAS_TYPE(PIP_ADAPTER_ADDRESSES, void*);
REGISTER_UMOCK_ALIAS_TYPE(PMIB_IPNET_TABLE2, void*);
REGISTER_UMOCK_ALIAS_TYPE(SOCKET, void*);
REGISTER_UMOCK_ALIAS_TYPE(PVOID, void*);
REGISTER_UMOCK_ALIAS_TYPE(LPVOID, void*);
REGISTER_UMOCK_ALIAS_TYPE(LPCVOID, void*);
REGISTER_UMOCK_ALIAS_TYPE(BOOL, bool);
END_DECLARE_TEST_SUITE()

//
// 4. Setup and run tests
//
DECLARE_TEST_SETUP()

#if defined pal_scan_init
//
// Test pal_scan_init happy path
//
EST_FUNCTION(pal_win_scan_init__success)
{
    int32_t result;

    // arrange
    // ...

    // act
    result = pal_scan_init();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_ok, result);
    // ...
}

//
// Test pal_scan_init unhappy path
//
EST_FUNCTION(pal_win_scan_init__neg)
{
    int32_t result;

    ASSERT_ARE_EQUAL(int, 0, umock_c_negative_tests_init());

    // arrange
    UMOCK_C_NEGATIVE_TESTS_ARRANGE();
    // ...

    // act
    UMOCK_C_NEGATIVE_TESTS_ACT();
    result = pal_scan_init();

    // assert
    UMOCK_C_NEGATIVE_TESTS_ASSERT(int32_t, result, er_ok);
}

#endif //  pal_scan_init

#if defined pal_ipscan
//
// Test pal_ipscan happy path
//
EST_FUNCTION(pal_win_ipscan__success)
{
    static const int32_t k_flags_valid;
    static const uint16_t k_port_valid;
    static const pal_scan_cb_t k_cb_valid;
    static const void* k_context_valid;
    int32_t result;

    // arrange
    // ...

    // act
    result = pal_ipscan(k_flags_valid, k_port_valid, k_cb_valid, k_context_valid);

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_ok, result);
    // ...
}

//
// Test pal_ipscan passing as flags argument an invalid int32_t value
//
EST_FUNCTION(pal_win_ipscan__arg_flags_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_ipscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_ipscan passing as port argument an invalid uint16_t value
//
EST_FUNCTION(pal_win_ipscan__arg_port_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_ipscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_ipscan passing as cb argument an invalid pal_scan_cb_t value
//
EST_FUNCTION(pal_win_ipscan__arg_cb_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_ipscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_ipscan passing as context argument an invalid void* value
//
EST_FUNCTION(pal_win_ipscan__arg_context_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_ipscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_ipscan unhappy path
//
EST_FUNCTION(pal_win_ipscan__neg)
{
    static const int32_t k_flags_valid;
    static const uint16_t k_port_valid;
    static const pal_scan_cb_t k_cb_valid;
    static const void* k_context_valid;
    int32_t result;

    ASSERT_ARE_EQUAL(int, 0, umock_c_negative_tests_init());

    // arrange
    UMOCK_C_NEGATIVE_TESTS_ARRANGE();
    // ...

    // act
    UMOCK_C_NEGATIVE_TESTS_ACT();
    result = pal_ipscan(k_flags_valid, k_port_valid, k_cb_valid, k_context_valid);

    // assert
    UMOCK_C_NEGATIVE_TESTS_ASSERT(int32_t, result, er_ok);
}

#endif //  pal_ipscan

#if defined pal_portscan
//
// Test pal_portscan happy path
//
EST_FUNCTION(pal_win_portscan__success)
{
    static const prx_socket_address_t* k_addr_valid;
    static const uint16_t k_port_range_low_valid;
    static const uint16_t k_port_range_high_valid;
    static const int32_t k_flags_valid;
    static const pal_scan_cb_t k_cb_valid;
    static const void* k_context_valid;
    int32_t result;

    // arrange
    // ...

    // act
    result = pal_portscan(k_addr_valid, k_port_range_low_valid, k_port_range_high_valid, k_flags_valid, k_cb_valid, k_context_valid);

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_ok, result);
    // ...
}

//
// Test pal_portscan passing as addr argument an invalid prx_socket_address_t* value
//
EST_FUNCTION(pal_win_portscan__arg_addr_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan passing as port_range_low argument an invalid uint16_t value
//
EST_FUNCTION(pal_win_portscan__arg_port_range_low_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan passing as port_range_high argument an invalid uint16_t value
//
EST_FUNCTION(pal_win_portscan__arg_port_range_high_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan passing as flags argument an invalid int32_t value
//
EST_FUNCTION(pal_win_portscan__arg_flags_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan passing as cb argument an invalid pal_scan_cb_t value
//
EST_FUNCTION(pal_win_portscan__arg_cb_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan passing as context argument an invalid void* value
//
EST_FUNCTION(pal_win_portscan__arg_context_invalid)
{
    // ...
    int32_t result;

    // arrange
    // ...

    // act
    handle = pal_portscan();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(int32_t, er_fault, result);
    // ...
}

//
// Test pal_portscan unhappy path
//
EST_FUNCTION(pal_win_portscan__neg)
{
    static const prx_socket_address_t* k_addr_valid;
    static const uint16_t k_port_range_low_valid;
    static const uint16_t k_port_range_high_valid;
    static const int32_t k_flags_valid;
    static const pal_scan_cb_t k_cb_valid;
    static const void* k_context_valid;
    int32_t result;

    ASSERT_ARE_EQUAL(int, 0, umock_c_negative_tests_init());

    // arrange
    UMOCK_C_NEGATIVE_TESTS_ARRANGE();
    // ...

    // act
    UMOCK_C_NEGATIVE_TESTS_ACT();
    result = pal_portscan(k_addr_valid, k_port_range_low_valid, k_port_range_high_valid, k_flags_valid, k_cb_valid, k_context_valid);

    // assert
    UMOCK_C_NEGATIVE_TESTS_ASSERT(int32_t, result, er_ok);
}

#endif //  pal_portscan

#if defined pal_scan_deinit
//
// Test pal_scan_deinit happy path
//
EST_FUNCTION(pal_win_scan_deinit__success)
{
    void result;

    // arrange
    // ...

    // act
    result = pal_scan_deinit();

    // assert
    ASSERT_EXPECTED_CALLS();
    ASSERT_ARE_EQUAL(void, er_ok, result);
    // ...
}

//
// Test pal_scan_deinit unhappy path
//
EST_FUNCTION(pal_win_scan_deinit__neg)
{
    void result;

    ASSERT_ARE_EQUAL(int, 0, umock_c_negative_tests_init());

    // arrange
    UMOCK_C_NEGATIVE_TESTS_ARRANGE();
    // ...

    // act
    UMOCK_C_NEGATIVE_TESTS_ACT();
    result = pal_scan_deinit();

    // assert
    UMOCK_C_NEGATIVE_TESTS_ASSERT(void, result, er_ok);
}

#endif //  pal_scan_deinit


//
// 5. Teardown tests and test suite
//
DECLARE_TEST_COMPLETE()

