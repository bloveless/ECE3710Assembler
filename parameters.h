//
// Created by Brennon Loveless on 11/15/15.
//

#ifndef ASSEMBLER_MAIN_H_H
#define ASSEMBLER_MAIN_H_H

#include <map>

enum instructionType {
    NOOP,
    RTYPE,
    ITYPE,
    JTYPE,
    BTYPE,
    WTYPE /* wait type */,
    MTYPE /* memory type */,
    WLSTYPE /* wireless type */,
};

typedef struct {
    instructionType type;
    std::string     code;
    std::string     extCode;
    int             arguments;
} asmType;

std::map<std::string, asmType> initAsmCollection() {

    std::map<std::string, asmType> asmCollection;

    asmCollection["NOOP"] = (asmType) {
            .type      = NOOP,
            .code      = "0000",
            .extCode   = "0000",
            .arguments = 0
    };

    asmCollection["AND"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "0001",
            .arguments = 2
    };

    asmCollection["OR"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "0010",
            .arguments = 2
    };

    asmCollection["XOR"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "0011",
            .arguments = 2
    };

    asmCollection["ADD"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "0101",
            .arguments = 2
    };

    asmCollection["SUB"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "1001",
            .arguments = 2
    };

    asmCollection["CMP"] = (asmType) {
            .type      = RTYPE,
            .code      = "0000",
            .extCode   = "1011",
            .arguments = 2
    };

    asmCollection["ADDI"] = (asmType) {
            .type      = ITYPE,
            .code      = "0101",
            .extCode   = "0000",
            .arguments = 2
    };

    /*

    asmCollection["LSHIL"] = (asmType) {
            .type      = ITYPE,
            .code      = "1000",
            .extCode   = "0000",
            .arguments = 2
    };

    asmCollection["LSHIR"] = (asmType) {
            .type      = ITYPE,
            .code      = "1000",
            .extCode   = "0001",
            .arguments = 2
    };

    asmCollection["ASHIL"] = (asmType) {
            .type      = ITYPE,
            .code      = "1000",
            .extCode   = "0010",
            .arguments = 2
    };

    asmCollection["ASHIR"] = (asmType) {
            .type      = ITYPE,
            .code      = "1000",
            .extCode   = "0011",
            .arguments = 2
    };

     */

    asmCollection["LSH"] = (asmType) {
            .type      = ITYPE,
            .code      = "1000",
            .extCode   = "0000",
            .arguments = 2
    };

    /*

    asmCollection["ASHU"] = (asmType) {
            .type      = RTYPE,
            .code      = "1000",
            .extCode   = "0110",
            .arguments = 2
    };

     */

    asmCollection["SUBI"] = (asmType) {
            .type      = ITYPE,
            .code      = "1001",
            .extCode   = "0000",
            .arguments = 2
    };

    asmCollection["CMPI"] = (asmType) {
            .type      = ITYPE,
            .code      = "1011",
            .extCode   = "0000",
            .arguments = 2
    };

    asmCollection["SETI"] = (asmType) {
            .type      = ITYPE,
            .code      = "1010",
            .extCode   = "0000",
            .arguments = 2
    };

    asmCollection["JMP"] = (asmType) {
            .type      = JTYPE,
            .code      = "0100",
            .extCode   = "0000",
            .arguments = 1
    };

    asmCollection["LOAD"] = (asmType) {
            .type      = MTYPE,
            .code      = "0001",
            .extCode   = "0000",
            .arguments = 2
    };

    asmCollection["STOR"] = (asmType) {
            .type      = MTYPE,
            .code      = "0010",
            .extCode   = "0000",
            .arguments = 2

    };

    asmCollection["WAIT"] = (asmType) {
            .type      = WTYPE,
            .code      = "0011",
            .extCode   = "0000",
            .arguments = 1
    };

    asmCollection["WLS"] = (asmType) {
            .type      = WLSTYPE,
            .code      = "1111",
            .extCode   = "0000",
            .arguments = 1
    };

    asmCollection["BGE"] = (asmType) {
            .type      = BTYPE,
            .code      = "0111",
            .extCode   = "0000",
            .arguments = 1
    };

    asmCollection["TCHBRCH"] = (asmType) {
            .type      = BTYPE,
            .code      = "0110",
            .extCode   = "0000",
            .arguments = 1
    };

    return asmCollection;
};

#endif //ASSEMBLER_MAIN_H_H
