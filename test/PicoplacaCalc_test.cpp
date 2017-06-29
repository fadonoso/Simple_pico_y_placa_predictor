#include "gtest/gtest.h"
#include "PicoplacaCalc.h"


string fileName("config.cfg");
PicoplacaCalc picoplaca(fileName);


TEST(picoPlaca, truePrediction)
{
    query request;
    request.plate = "abcd137";
    request.date = "29-06-2017";
    request.time = "10:30:01";
    picoplaca.setQuery(request);
    EXPECT_EQ(picoplaca.predictor(), true);
}

TEST(picoPlaca, falsePrediction)
{
    query request;
    request.plate = "abcd137";
    request.date = "29-06-2017";
    request.time = "09:25:01";
    picoplaca.setQuery(request);
    EXPECT_EQ(picoplaca.predictor(), false);
}

TEST(picoPlaca, badDateFormat1)
{
    query request;
    request.plate = "abcd137";
    request.date = "51-06-2017";
    request.time = "10:30:01";
    EXPECT_EQ(picoplaca.setQuery(request), false);
}

TEST(picoPlaca, badDateFormat2)
{
    query request;
    request.plate = "abcd137";
    request.date = "safdsf";
    request.time = "10:30:01";
    EXPECT_EQ(picoplaca.setQuery(request), false);
}

TEST(picoPlaca, badTimeFormat1)
{
    query request;
    request.plate = "abcd137";
    request.date = "12-06-2017";
    request.time = "31:30:01";
    EXPECT_EQ(picoplaca.setQuery(request), false);
}

TEST(picoPlaca, badTimeFormat2)
{
    query request;
    request.plate = "abcd137";
    request.date = "13-06-2017";
    request.time = "dgfhggh";
    EXPECT_EQ(picoplaca.setQuery(request), false);
}

TEST(picoPlaca, badPlateFormat)
{
    query request;
    request.plate = "abcddsdfd";
    request.date = "13-06-2017";
    request.time = "10:30:01";
    EXPECT_EQ(picoplaca.setQuery(request), false);
}
