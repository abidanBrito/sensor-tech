/*  ------------------------------------------------------------------------
    AUTHOR:         Abidan Brito Clavijo
    FILE:           fileName.cpp
    DATE:           DD/MM/YYYY
    STATE:          TBD
    FUNCTIONALITY:  Describe what this file is used for.
    ------------------------------------------------------------------------
    NOTICE: (C) Copyright 2019 by Abidan Brito Clavijo. All rights reserved.
    ------------------------------------------------------------------------ */
#include "REST_Server.h"

void setup() {
    setupHTTP();
}

void loop() {
    loopHTTP(50, 50, 25, 5, 1020, 15, 1024, 1024);
}
