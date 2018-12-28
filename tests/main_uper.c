#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "files/c_source/c_source/uper.h"

static bool fequal(double v1, double v2)
{
    return (fabs(v1 - v2) < 0.000001);
}

static void test_uper_c_source_a(void)
{
    uint8_t encoded[50];
    struct uper_c_source_a_t decoded;

    /* Encode. */
    decoded.a = -1;
    decoded.b = -2;
    decoded.c = -3;
    decoded.d = -4;
    decoded.e = 1;
    decoded.f = 2;
    decoded.g = 3;
    decoded.h = 4;
    decoded.i = 1.0f;
    decoded.j = 1.0;
    decoded.k = true;
    memset(&decoded.l.value[0], 5, sizeof(decoded.l.value));

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_a_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x7f\x7f\xfe\x7f\xff\xff\xfd\x7f\xff\xff\xff\xff\xff"
                  "\xff\xfc\x01\x00\x02\x00\x00\x00\x03\x00\x00\x00\x00"
                  "\x00\x00\x00\x04\x03\x80\x00\x01\x03\x80\x00\x01\x82"
                  "\x82\x82\x82\x82\x82\x82\x82\x82\x82\x82\x80",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_a_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.a == -1);
    assert(decoded.b == -2);
    assert(decoded.c == -3);
    assert(decoded.d == -4);
    assert(decoded.e == 1);
    assert(decoded.f == 2);
    assert(decoded.g == 3);
    assert(decoded.h == 4);
    assert(fequal(decoded.i, 1.0f));
    assert(fequal(decoded.j, 1.0));
    assert(decoded.k);
    assert(memcmp(&decoded.l.value[0],
                  "\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05",
                  sizeof(decoded.l.value)) == 0);
}

static void test_uper_c_source_a_encode_error_no_mem(void)
{
    uint8_t encoded[49];
    struct uper_c_source_a_t decoded;

    decoded.a = -1;
    decoded.b = -2;
    decoded.c = -3;
    decoded.d = -4;
    decoded.e = 1;
    decoded.f = 2;
    decoded.g = 3;
    decoded.h = 4;
    decoded.i = 1.0f;
    decoded.j = 1.0;
    decoded.k = true;
    memset(&decoded.l.value[0], 5, sizeof(decoded.l.value));

    assert(uper_c_source_a_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == -ENOMEM);
}

static void test_uper_c_source_a_decode_error_out_of_data(void)
{
    uint8_t encoded[49] =
        "\x7f\x7f\xfe\x7f\xff\xff\xfd\x7f\xff\xff\xff\xff\xff"
        "\xff\xfc\x01\x00\x02\x00\x00\x00\x03\x00\x00\x00\x00"
        "\x00\x00\x00\x04\x03\x80\x00\x01\x03\x80\x00\x01\x82"
        "\x82\x82\x82\x82\x82\x82\x82\x82\x82\x82";
    struct uper_c_source_a_t decoded;

    assert(uper_c_source_a_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == -EOUTOFDATA);
}

static void test_uper_c_source_b_choice_a(void)
{
    uint8_t encoded[2];
    struct uper_c_source_b_t decoded;

    /* Encode. */
    decoded.choice = uper_c_source_b_choice_a_t;
    decoded.value.a = -10;

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_b_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x1d\x80",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_b_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.choice == uper_c_source_b_choice_a_t);
    assert(decoded.value.a == -10);
}

static void test_uper_c_source_b_choice_b(void)
{
    uint8_t encoded[50];
    struct uper_c_source_b_t decoded;

    /* Encode. */
    decoded.choice = uper_c_source_b_choice_b_t;
    decoded.value.b.a = -1;
    decoded.value.b.b = -2;
    decoded.value.b.c = -3;
    decoded.value.b.d = -4;
    decoded.value.b.e = 1;
    decoded.value.b.f = 2;
    decoded.value.b.g = 3;
    decoded.value.b.h = 4;
    decoded.value.b.i = 1.0f;
    decoded.value.b.j = 1.0;
    decoded.value.b.k = true;
    memset(&decoded.value.b.l.value[0], 5, sizeof(decoded.value.b.l.value));

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_b_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x5f\xdf\xff\x9f\xff\xff\xff\x5f\xff\xff\xff\xff\xff"
                  "\xff\xff\x00\x40\x00\x80\x00\x00\x00\xc0\x00\x00\x00"
                  "\x00\x00\x00\x01\x00\xe0\x00\x00\x40\xe0\x00\x00\x60"
                  "\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_b_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.choice == uper_c_source_b_choice_b_t);
    assert(decoded.value.b.a == -1);
    assert(decoded.value.b.b == -2);
    assert(decoded.value.b.c == -3);
    assert(decoded.value.b.d == -4);
    assert(decoded.value.b.e == 1);
    assert(decoded.value.b.f == 2);
    assert(decoded.value.b.g == 3);
    assert(decoded.value.b.h == 4);
    assert(fequal(decoded.value.b.i, 1.0f));
    assert(fequal(decoded.value.b.j, 1.0));
    assert(decoded.value.b.k);
    assert(memcmp(&decoded.value.b.l.value[0],
                  "\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05",
                  sizeof(decoded.value.b.l.value)) == 0);
}

static void test_uper_c_source_b_decode_error_bad_choice(void)
{
    uint8_t encoded[2] = "\xdd\x80";
    struct uper_c_source_b_t decoded;

    assert(uper_c_source_b_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == -EBADCHOICE);
}

static void test_uper_c_source_d_all_present(void)
{
    uint8_t encoded[10];
    struct uper_c_source_d_t decoded;

    /* Encode. */
    decoded.length = 1;
    decoded.elements[0].a.b.choice = uper_c_source_d_a_b_choice_c_t;
    decoded.elements[0].a.b.value.c = 0;
    decoded.elements[0].a.e.length = 3;
    decoded.elements[0].g.h = uper_c_source_d_g_h_j_t;
    decoded.elements[0].g.l.length = 2;
    decoded.elements[0].g.l.value[0] = 0x54;
    decoded.elements[0].g.l.value[1] = 0x55;
    decoded.elements[0].m.is_n_present = true;
    decoded.elements[0].m.n = false;
    decoded.elements[0].m.o = 2;
    decoded.elements[0].m.is_p_present = true;
    memset(&decoded.elements[0].m.p.q.value[0],
           3,
           sizeof(decoded.elements[0].m.p.q.value));
    decoded.elements[0].m.p.is_r_present = true;
    decoded.elements[0].m.p.r = true;

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_d_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x00\xd5\x15\x7a\xc0\xc0\xc0\xc0\xc0\xe0",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_d_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.length == 1);
    assert(decoded.elements[0].a.b.choice == uper_c_source_d_a_b_choice_c_t);
    assert(decoded.elements[0].a.b.value.c == 0);
    assert(decoded.elements[0].a.e.length == 3);
    assert(decoded.elements[0].g.h == uper_c_source_d_g_h_j_t);
    assert(decoded.elements[0].g.l.length == 2);
    assert(decoded.elements[0].g.l.value[0] == 0x54);
    assert(decoded.elements[0].g.l.value[1] == 0x55);
    assert(decoded.elements[0].m.is_n_present);
    assert(decoded.elements[0].m.n == false);
    assert(decoded.elements[0].m.o == 2);
    assert(decoded.elements[0].m.is_p_present);
    assert(memcmp(&decoded.elements[0].m.p.q.value[0],
                  "\x03\x03\x03\x03\x03",
                  sizeof(decoded.elements[0].m.p.q.value)) == 0);
    assert(decoded.elements[0].m.p.is_r_present);
    assert(decoded.elements[0].m.p.r == true);
}

static void test_uper_c_source_e(void)
{
    uint8_t encoded[1];
    struct uper_c_source_e_t decoded;

    /* Encode. */
    decoded.a.choice = uper_c_source_e_a_choice_b_t;
    decoded.a.value.b.choice = uper_c_source_e_a_b_choice_c_t;
    decoded.a.value.b.value.c = true;

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_e_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x80",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_e_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.a.choice == uper_c_source_e_a_choice_b_t);
    assert(decoded.a.value.b.choice == uper_c_source_e_a_b_choice_c_t);
    assert(decoded.a.value.b.value.c == true);
}

static void test_uper_c_source_f(void)
{
    uint8_t encoded[1];
    struct uper_c_source_f_t decoded;

    /* Encode. */
    decoded.length = 2;
    decoded.elements[0].elements[0] = false;
    decoded.elements[1].elements[0] = true;

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_f_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\xa0",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_f_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.length == 2);
    assert(decoded.elements[0].elements[0] == false);
    assert(decoded.elements[1].elements[0] == true);
}

static void test_uper_c_source_g(void)
{
    uint8_t encoded[2];
    struct uper_c_source_g_t decoded;

    /* Encode. */
    decoded.is_a_present = true;
    decoded.a = true;
    decoded.is_b_present = false;
    decoded.is_c_present = false;
    decoded.is_d_present = false;
    decoded.is_e_present = false;
    decoded.is_f_present = false;
    decoded.is_g_present = false;
    decoded.is_h_present = false;
    decoded.is_i_present = true;
    decoded.i = true;

    memset(&encoded[0], 0, sizeof(encoded));
    assert(uper_c_source_g_encode(&encoded[0],
                                  sizeof(encoded),
                                  &decoded) == sizeof(encoded));
    assert(memcmp(&encoded[0],
                  "\x80\xe0",
                  sizeof(encoded)) == 0);

    /* Decode. */
    memset(&decoded, 0, sizeof(decoded));
    assert(uper_c_source_g_decode(&decoded,
                                  &encoded[0],
                                  sizeof(encoded)) == sizeof(encoded));

    assert(decoded.is_a_present);
    assert(decoded.a == true);
    assert(!decoded.is_b_present);
    assert(!decoded.is_c_present);
    assert(!decoded.is_d_present);
    assert(!decoded.is_e_present);
    assert(!decoded.is_f_present);
    assert(!decoded.is_g_present);
    assert(!decoded.is_h_present);
    assert(decoded.is_i_present);
    assert(decoded.i == true);
}

int main(void)
{
    test_uper_c_source_a();
    test_uper_c_source_a_encode_error_no_mem();
    test_uper_c_source_a_decode_error_out_of_data();

    test_uper_c_source_b_choice_a();
    test_uper_c_source_b_choice_b();
    test_uper_c_source_b_decode_error_bad_choice();

    test_uper_c_source_d_all_present();

    test_uper_c_source_e();
    test_uper_c_source_f();
    test_uper_c_source_g();

    return (0);
}
