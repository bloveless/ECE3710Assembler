//
// Created by Brennon Loveless on 11/15/15.
//

#ifndef ASSEMBLER_MAIN_H_H
#define ASSEMBLER_MAIN_H_H

#include <map>

enum instructionType {
    NOOP, RTYPE, ITYPE, JTYPE, WTYPE /* wait type */, MTYPE /* memory type */
};

typedef struct {
    instructionType type;
    std::string code;
    std::string extCode;
} asmType;

std::map<std::string, asmType> initAsmCollection() {

    std::map<std::string, asmType> asmCollection;

    asmCollection["NOOP"] = (asmType) {
            .type    = NOOP,
            .code    = "0000",
            .extCode = "0000"
    };

    asmCollection["AND"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "0001"
    };

    asmCollection["OR"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "0010"
    };

    asmCollection["XOR"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "0011"
    };

    asmCollection["ADD"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "0101"
    };

    asmCollection["SUB"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "1001"
    };

    asmCollection["CMP"] = (asmType) {
            .type    = RTYPE,
            .code    = "0000",
            .extCode = "1011"
    };

    asmCollection["ADDI"] = (asmType) {
            .type    = ITYPE,
            .code    = "0101",
            .extCode = "0000"
    };

    asmCollection["LSHIL"] = (asmType) {
            .type    = ITYPE,
            .code    = "1000",
            .extCode = "0000"
    };

    asmCollection["LSHIR"] = (asmType) {
            .type    = ITYPE,
            .code    = "1000",
            .extCode = "0001"
    };

    asmCollection["ASHIL"] = (asmType) {
            .type    = ITYPE,
            .code    = "1000",
            .extCode = "0010"
    };

    asmCollection["ASHIR"] = (asmType) {
            .type    = ITYPE,
            .code    = "1000",
            .extCode = "0011"
    };

    asmCollection["LSH"] = (asmType) {
            .type    = RTYPE,
            .code    = "1000",
            .extCode = "0100"
    };

    asmCollection["ASHU"] = (asmType) {
            .type    = RTYPE,
            .code    = "1000",
            .extCode = "0110"
    };

    asmCollection["SUBI"] = (asmType) {
            .type    = ITYPE,
            .code    = "1001",
            .extCode = "0000"
    };

    asmCollection["CMPI"] = (asmType) {
            .type    = ITYPE,
            .code    = "1011",
            .extCode = "0000"
    };

    asmCollection["SETI"] = (asmType) {
            .type    = ITYPE,
            .code    = "1010",
            .extCode = "0000"
    };

    asmCollection["JMP"] = (asmType) {
            .type    = JTYPE,
            .code    = "0100",
            .extCode = "0000"
    };

    asmCollection["LOAD"] = (asmType) {
            .type    = MTYPE,
            .code    = "0001",
            .extCode = "0000"
    };

    asmCollection["STOR"] = (asmType) {
            .type    = MTYPE,
            .code    = "0010",
            .extCode = "0000"
    };

    asmCollection["WAIT"] = (asmType) {
            .type    = WTYPE,
            .code    = "0011",
            .extCode = "0000"
    };

    return asmCollection;
};

#endif //ASSEMBLER_MAIN_H_H
