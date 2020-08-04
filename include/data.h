#ifndef DEFS_H
#define DEFS_H
#include "defs.h"
#endif

Rule parseTable[32][29];

void buildTable(Rule table[32][29]){
    EntryType temp[9];

    //<Program> -- $
    temp[0].type = 3;
    Rule ProEnd = {1, {temp[0]}};
    table[PROGRAM][END] = ProEnd;

    //<Program> -- fn
    temp[0].type = 0;
    temp[0].datum.nonTerminal = DEF;
    Rule ProFn = {1, {temp[0]}};
    table[PROGRAM][FN] = ProFn;

    //<Def> -- $
    temp[0].type = 3;
    Rule DefEnd = {1, {temp[0]}};
    table[DEF][END] = DefEnd;

    //<DEF> -- fn
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FUNCTION;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = DEF;
    Rule DefFn = {2, {temp[0],temp[1]}};
    table[DEF][FN] = DefFn;

    //<Function> -- fn
    temp[0].type = 1;
    temp[0].datum.terminal.token = FN;
    temp[1].type = 1;
    temp[1].datum.terminal.token = IDENTIFIER;
    temp[2].type = 1;
    temp[2].datum.terminal.token = OPENPAREN;
    temp[3].type = 0;
    temp[3].datum.nonTerminal = FORMALLIST;
    temp[4].type = 1;
    temp[4].datum.terminal.token = CLOSEPAREN;
    temp[5].type = 1;
    temp[5].datum.terminal.token = TYPE;
    temp[6].type = 1;
    temp[6].datum.terminal.token = OPENCURL;
    temp[7].type = 0;
    temp[7].datum.nonTerminal = BODY;
    temp[8].type = 1;
    temp[8].datum.terminal.token = CLOSECURL;
    Rule FunFn = {9, {temp[0], temp[1], temp[2], temp[3], temp[4],
                      temp[5], temp[6], temp[7], temp[8]}};
    table[FUNCTION][FN] = FunFn;

    // <FormalList> -- )
    temp[0].type = 3;
    Rule ForlCp = {1, {temp[0]}};
    table[FORMALLIST][CLOSEPAREN] = ForlCp;

    // <FormalList> -- Type (int, bol, vct, mat)
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEFORMAL;
    Rule ForlType = {1, {temp[0]}};
    table[FORMALLIST][TYPE] = ForlType;

    // <NEFormal> -- Type (int, bol, vct, mat)
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FORMAL;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEFORMALTAIL;
    Rule NEFType = {2, {temp[0], temp[1]}};
    table[NEFORMAL][TYPE] = NEFType;

    // <NEFormal-Tail> -- )
    temp[0].type = 3;
    Rule NEFTCp = {1, {temp[0]}};
    table[NEFORMALTAIL][CLOSEPAREN] = NEFTCp;

    // <NEFormal-Tail> -- ,
    temp[0].type = 1;
    temp[0].datum.terminal.token = COMMA;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEFORMAL;
    Rule NEFTCo = {2, {temp[0], temp[1]}};
    table[NEFORMALTAIL][COMMA] = NEFTCo;

    // <Formal> -- Type
    temp[0].type = 1;
    temp[0].datum.terminal.token = TYPE;
    temp[1].type = 1;
    temp[1].datum.terminal.token = IDENTIFIER;
    Rule ForType = {2, {temp[0], temp[1]}};
    table[FORMAL][TYPE] = ForType;

    // <Body> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodOp = {1, {temp[0]}};
    table[BODY][OPENPAREN] = BodOp;

    // <Body> -- }
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodCc = {1, {temp[0]}};
    table[BODY][CLOSECURL] = BodCc;

    // <Body> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodEx = {1, {temp[0]}};
    table[BODY][EXCLAIM] = BodEx;

    // <Body> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodMn = {1, {temp[0]}};
    table[BODY][MINUS] = BodMn;

    // <Body> -- Type
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodType = {1, {temp[0]}};
    table[BODY][TYPE] = BodType;

    // <Body> -- print
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodPrint = {1, {temp[0]}};
    table[BODY][PRINT] = BodPrint;

    // <Body> -- if
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule Bodif = {1, {temp[0]}};
    table[BODY][IF] = Bodif;

    // <Body> -- return
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodRt = {1, {temp[0]}};
    table[BODY][RETURN] = BodRt;

    // <Body> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodId = {1, {temp[0]}};
    table[BODY][IDENTIFIER] = BodId;

    // <Body> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodInt = {1, {temp[0]}};
    table[BODY][INTEGER] = BodInt;

    // <Body> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodBol = {1, {temp[0]}};
    table[BODY][BOOLEAN] = BodBol;

    // <Body> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodOb = {1, {temp[0]}};
    table[BODY][OPENBRAKET] = BodOb;

    // <Body> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEBODY;
    Rule BodVc = {1, {temp[0]}};
    table[BODY][VOPENBRAKET] = BodVc;

    // <NEBody> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBOp = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][OPENPAREN] = NEBOp;

    // <NEBody> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBMn = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][MINUS] = NEBMn;

    // <NEBody> -- print
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBPrint = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][PRINT] = NEBPrint;

    // <NEBody> -- if
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBIf = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][IF] = NEBIf;

    // <NEBody> -- return
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBRt = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][RETURN] = NEBRt;

    // <NEBody> -- id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBId = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][IDENTIFIER] = NEBId;

    // <NEBody> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBInt = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][INTEGER] = NEBInt;

    // <NEBody> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBBol = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][BOOLEAN] = NEBBol;

    // <NEBody> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBOb = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][OPENBRAKET] = NEBOb;

    // <NEBody> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = STATEMENT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = SEMICOLON;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = BODY;
    Rule NEBVc = {3, {temp[0], temp[1], temp[2]}};
    table[NEBODY][VOPENBRAKET] = NEBVc;

    // <Statement> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StOp = {1, {temp[0]}};
    table[STATEMENT][OPENPAREN] = StOp;

    // <Statement> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StEx = {1, {temp[0]}};
    table[STATEMENT][EXCLAIM] = StEx;

    // <Statement> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StMn = {1, {temp[0]}};
    table[STATEMENT][MINUS] = StMn;

    // <Statement> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StId = {1, {temp[0]}};
    table[STATEMENT][IDENTIFIER] = StId;

    // <Statement> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StInt = {1, {temp[0]}};
    table[STATEMENT][INTEGER] = StInt;

    // <Statement> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;;
    Rule StBol = {1, {temp[0]}};
    table[STATEMENT][BOOLEAN] = StBol;

    // <Statement> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StOb = {1, {temp[0]}};
    table[STATEMENT][OPENBRAKET] = StOb; 

    // <Statement> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    Rule StVb = {1, {temp[0]}};
    table[STATEMENT][VOPENBRAKET] = StVb;

    // <Statement> -- Type
    temp[0].type = 1;
    temp[0].datum.terminal.token = TYPE;
    temp[1].type = 1;
    temp[1].datum.terminal.token = IDENTIFIER;
    temp[2].type = 1;
    temp[2].datum.terminal.token = EQUALS;
    temp[3].type = 0;
    temp[3].datum.nonTerminal = EXPR;
    Rule StTp = {4, {temp[0], temp[1], temp[2], temp[3]}};
    table[STATEMENT][TYPE] = StTp;

    // <Statement> -- print
    temp[0].type = 1;
    temp[0].datum.terminal.token = PRINT;
    temp[1].type = 1;
    temp[1].datum.terminal.token = OPENPAREN;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = EXPR;
    temp[3].type = 1;
    temp[3].datum.terminal.token = CLOSEPAREN;
    Rule StPrint = {4, {temp[0], temp[1], temp[2], temp[3]}};
    table[STATEMENT][PRINT] = StPrint;

    // <Statement> -- if
    temp[0].type = 1;
    temp[0].datum.terminal.token = IF;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    temp[2].type = 1;
    temp[2].datum.terminal.token = OPENCURL;
    temp[3].type = 0;
    temp[3].datum.nonTerminal = BODY;
    temp[4].type = 1;
    temp[4].datum.terminal.token = CLOSECURL;
    temp[5].type = 1;
    temp[5].datum.terminal.token = ELSE;
    temp[6].type = 1;
    temp[6].datum.terminal.token = OPENCURL;
    temp[7].type = 0;
    temp[7].datum.nonTerminal = BODY;
    temp[8].type = 1;
    temp[8].datum.terminal.token = CLOSECURL;
    Rule StIf = {8, {temp[0], temp[1], temp[2], temp[3],
                     temp[4], temp[5], temp[6], temp[7]}};
    table[STATEMENT][IF] = StIf;

    // <Statement> -- return
    temp[0].type = 1;
    temp[0].datum.terminal.token = RETURN;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    Rule StRt = {2, {temp[0], temp[1]}};
    table[STATEMENT][RETURN] = StRt;

    // <EXPR> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExOp = {2, {temp[0], temp[1]}};
    table[EXPR][OPENPAREN] = ExOp;

    // <EXPR> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExEx = {2, {temp[0], temp[1]}};
    table[EXPR][EXCLAIM] = ExEx;

    // <EXPR> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExMn = {2, {temp[0], temp[1]}};
    table[EXPR][MINUS] = ExMn;

    // <EXPR> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExId = {2, {temp[0], temp[1]}};
    table[EXPR][IDENTIFIER] = ExId;

    // <EXPR> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExInt = {2, {temp[0], temp[1]}};
    table[EXPR][INTEGER] = ExInt;

    // <EXPR> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExBool = {2, {temp[0], temp[1]}};
    table[EXPR][BOOLEAN] = ExBool;

    // <EXPR> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExOb = {2, {temp[0], temp[1]}};
    table[EXPR][OPENPAREN] = ExOb;

    // <EXPR> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = SIMPLEEXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPRTAIL;
    Rule ExVop = {2, {temp[0], temp[1]}};
    table[EXPR][VOPENBRAKET] = ExVop;

    // <EXPR-Tail> -- )
    temp[0].type = 3;
    Rule EXTCp = {1, {temp[0]}};
    table[EXPRTAIL][CLOSEPAREN] = EXTCp;

    // <EXPR-Tail> -- {
    temp[0].type = 3;
    Rule EXTOc = {1, {temp[0]}};
    table[EXPRTAIL][OPENCURL] = EXTOc;

    // <EXPR-Tail> -- ,
    temp[0].type = 3;
    Rule EXTCo = {1, {temp[0]}};
    table[EXPRTAIL][COMMA] = EXTCo;

    // <EXPR-Tail> -- ;
    temp[0].type = 3;
    Rule EXTSc = {1, {temp[0]}};
    table[EXPRTAIL][SEMICOLON] = EXTSc;

    // <EXPR-Tail> -- *
    temp[0].type = 3;
    Rule EXTTm = {1, {temp[0]}};
    table[EXPRTAIL][TIMES] = EXTTm;

    // <EXPR-Tail> -- /
    temp[0].type = 3;
    Rule EXTDv = {1, {temp[0]}};
    table[EXPRTAIL][DIVIDE] = EXTDv;

    // <EXPR-Tail> -- -
    temp[0].type = 3;
    Rule EXTMn = {1, {temp[0]}};
    table[EXPRTAIL][MINUS] = EXTMn;

    // <EXPR-Tail> -- +
    temp[0].type = 3;
    Rule EXTPl = {1, {temp[0]}};
    table[EXPRTAIL][PLUS] = EXTPl;

    // <EXPR-Tail> -- and
    temp[0].type = 3;
    Rule EXTAn = {1, {temp[0]}};
    table[EXPRTAIL][AND] = EXTAn;

    // <EXPR-Tail> -- or
    temp[0].type = 3;
    Rule EXTOr = {1, {temp[0]}};
    table[EXPRTAIL][OR] = EXTOr;

    // <EXPR-Tail> -- ]
    temp[0].type = 3;
    Rule EXTCb = {1, {temp[0]}};
    table[EXPRTAIL][CLOSEBRAKET] = EXTCb;

    // <EXPR-Tail> -- <
    temp[0].type = 1;
    temp[0].datum.terminal.token = LESS;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    Rule EXTLs = {2, {temp[0], temp[1]}};
    table[EXPRTAIL][LESS] = EXTLs;

    // <EXPR-Tail> -- ==
    temp[0].type = 1;
    temp[0].datum.terminal.token = DEQUALS;
    temp[2].type = 0;
    temp[2].datum.nonTerminal = EXPR;
    Rule EXTEq = {2, {temp[0], temp[1]}};
    table[EXPRTAIL][DEQUALS] = EXTEq;

    // <Simple-Expr> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeOp = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][OPENPAREN] = SeOp;

    // <Simple-Expr> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeEx = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][EXCLAIM] = SeEx;

    // <Simple-Expr> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeMn = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][MINUS] = SeMn;

    // <Simple-Expr> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeId = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][IDENTIFIER] = SeId;

    // <Simple-Expr> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeInt = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][INTEGER] = SeInt;

    // <Simple-Expr> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeBool = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][BOOLEAN] = SeBool;

    // <Simple-Expr> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeOb = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][OPENBRAKET] = SeOb;

    // <Simple-Expr> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = TERM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLETAIL;
    Rule SeVb = {2, {temp[0], temp[1]}};
    table[SIMPLEEXPR][VOPENBRAKET] = SeVb;

    // <Simple-Tail> -- )
    temp[0].type = 3;
    Rule StCp = {1, {temp[0]}};
    table[SIMPLETAIL][CLOSEPAREN] = StCp;

    // <Simple-Tail> -- {
    temp[0].type = 3;
    Rule StOc = {1, {temp[0]}};
    table[SIMPLETAIL][OPENCURL] = StOc;

    // <Simple-Tail> -- ,
    temp[0].type = 3;
    Rule StCm = {1, {temp[0]}};
    table[SIMPLETAIL][COMMA] = StCm;

    // <Simple-Tail> -- ;
    temp[0].type = 3;
    Rule StSc = {1, {temp[0]}};
    table[SIMPLETAIL][SEMICOLON] = StSc;

    // <Simple-Tail> -- *
    temp[0].type = 3;
    Rule StTm = {1, {temp[0]}};
    table[SIMPLETAIL][TIMES] = StTm;

    // <Simple-Tail> -- /
    temp[0].type = 3;
    Rule StDv = {1, {temp[0]}};
    table[SIMPLETAIL][DIVIDE] = StDv;

    // <Simple-Tail> -- <
    temp[0].type = 3;
    Rule StLs = {1, {temp[0]}};
    table[SIMPLETAIL][LESS] = StLs;

    // <Simple-Tail> -- ==
    temp[0].type = 3;
    Rule StEq = {1, {temp[0]}};
    table[SIMPLETAIL][DEQUALS] = StEq;

    // <Simple-Tail> -- and
    temp[0].type = 3;
    Rule StAd = {1, {temp[0]}};
    table[SIMPLETAIL][AND] = StAd;

    // <Simple-Tail> -- or
    temp[0].type = 3;
    Rule StOr = {1, {temp[0]}};
    table[SIMPLETAIL][OR] = StOr;

    // <Simple-Tail> -- ]
    temp[0].type = 3;
    Rule StCb = {1, {temp[0]}};
    table[SIMPLETAIL][CLOSEBRAKET] = StCb;

    // <Simple-Tail> -- -
    temp[0].type = 1;
    temp[0].datum.terminal.token = MINUS;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLEEXPR;
    Rule SitMn = {2, {temp[0], temp[1]}};
    table[SIMPLETAIL][MINUS] = SitMn;
    
    // <Simple-Tail> -- +
    temp[0].type = 1;
    temp[0].datum.terminal.token = PLUS;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = SIMPLEEXPR;
    Rule StPL = {2, {temp[0], temp[1]}};
    table[SIMPLETAIL][PLUS] = StPL;

    // <Term> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmOp = {2, {temp[0], temp[1]}};
    table[TERM][OPENPAREN] = TmOp;

    // <Term> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmEx = {2, {temp[0], temp[1]}};
    table[TERM][EXCLAIM] = TmEx;

    // <Term> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmMn = {2, {temp[0], temp[1]}};
    table[TERM][MINUS] = TmMn;

    // <Term> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmId = {2, {temp[0], temp[1]}};
    table[TERM][IDENTIFIER] = TmId;

    // <Term> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmInt = {2, {temp[0], temp[1]}};
    table[TERM][INTEGER] = TmInt;

    // <Term> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmBool = {2, {temp[0], temp[1]}};
    table[TERM][BOOLEAN] = TmBool;

    // <Term> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmOb = {2, {temp[0], temp[1]}};
    table[TERM][OPENBRAKET] = TmOb;

    // <Term> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = FACTOR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERMTAIL;
    Rule TmVb = {2, {temp[0], temp[1]}};
    table[TERM][VOPENBRAKET] = TmVb;

    // <Term-Tail> -- )
    temp[0].type = 3;
    Rule TTCp = {1, {temp[0]}};
    table[TERMTAIL][CLOSEPAREN] = TTCp;

    // <Term-Tail> -- {
    temp[0].type = 3;
    Rule TTOc = {1, {temp[0]}};
    table[TERMTAIL][OPENCURL] = TTOc;

    // <Term-Tail> -- ,
    temp[0].type = 3;
    Rule TTCm = {1, {temp[0]}};
    table[TERMTAIL][COMMA] = TTCm;

    // <Term-Tail> -- ;
    temp[0].type = 3;
    Rule TTSc = {1, {temp[0]}};
    table[TERMTAIL][SEMICOLON] = TTSc;

    // <Term-Tail> -- -
    temp[0].type = 3;
    Rule TTMn = {1, {temp[0]}};
    table[TERMTAIL][MINUS] = TTMn;

    // <Term-Tail> -- +
    temp[0].type = 3;
    Rule TTPl = {1, {temp[0]}};
    table[TERMTAIL][PLUS] = TTPl;

    // <Term-Tail> -- <
    temp[0].type = 3;
    Rule TTLs = {1, {temp[0]}};
    table[TERMTAIL][LESS] = TTLs;

    // <Term-Tail> -- ==
    temp[0].type = 3;
    Rule TTEq = {1, {temp[0]}};
    table[TERMTAIL][DEQUALS] = TTEq;

    // <Term-Tail> -- ]
    temp[0].type = 3;
    Rule TTCb = {1, {temp[0]}};
    table[TERMTAIL][CLOSEBRAKET] = TTCb;

    // <Term-Tail> -- *
    temp[0].type = 1;
    temp[0].datum.terminal.token = TIMES;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERM;
    Rule TTTm = {2, {temp[0], temp[1]}};
    table[TERMTAIL][TIMES] = TTTm;

    // <Term-Tail> -- /
    temp[0].type = 1;
    temp[0].datum.terminal.token = DIVIDE;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERM;
    Rule TTDv = {2, {temp[0], temp[1]}};
    table[TERMTAIL][DIVIDE] = TTDv;

    // <Term-Tail> -- and
    temp[0].type = 1;
    temp[0].datum.terminal.token = AND;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERM;
    Rule TTAd = {2, {temp[0], temp[1]}};
    table[TERMTAIL][AND] = TTAd;

    // <Term-Tail> -- or
    temp[0].type = 1;
    temp[0].datum.terminal.token = OR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = TERM;
    Rule TTOr = {2, {temp[0], temp[1]}};
    table[TERMTAIL][OR] = TTOr;

    // <Factor> -- (
    temp[0].type = 1;
    temp[0].datum.terminal.token = OPENPAREN;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    temp[2].type = 1;
    temp[2].datum.terminal.token = CLOSEPAREN;
    Rule FaOp = {3, {temp[0], temp[1], temp[2]}};
    table[FACTOR][OPENPAREN] = FaOp;

    // <Factor> -- !
    temp[0].type = 1;
    temp[0].datum.terminal.token = EXCLAIM;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = FACTOR;
    Rule FaEx = {2, {temp[0], temp[1]}};
    table[FACTOR][EXCLAIM] = FaEx;

    // <Factor> -- -
    temp[0].type = 1;
    temp[0].datum.terminal.token = MINUS;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = FACTOR;
    Rule FaMn = {2, {temp[0], temp[1]}};
    table[FACTOR][MINUS] = FaMn;

    // <Factor> -- Id
    temp[0].type = 1;
    temp[0].datum.terminal.token = IDENTIFIER;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = FACTORTAIL;
    Rule FaId = {2, {temp[0], temp[1]}};
    table[FACTOR][IDENTIFIER] = FaId;

    // <Factor> -- Integer
    temp[0].type = 1;
    temp[0].datum.terminal.token = INTEGER;
    Rule FaInt = {1, {temp[0]}};
    table[FACTOR][INTEGER] = FaInt;

    // <Factor> -- Boolean
    temp[0].type = 1;
    temp[0].datum.terminal.token = BOOLEAN;
    Rule FaBool = {1, {temp[0]}};
    table[FACTOR][BOOLEAN] = FaBool;

    // <Factor> -- [
    temp[0].type = 1;
    temp[0].datum.terminal.token = OPENBRAKET;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = VCTLIST;
    temp[2].type = 1;
    temp[2].datum.terminal.token = CLOSEBRAKET;
    Rule FaOb = {3, {temp[0], temp[1], temp[2]}};
    table[FACTOR][OPENBRAKET] = FaOb;

    // <Factor> -- v[
    temp[0].type = 1;
    temp[0].datum.terminal.token = VOPENBRAKET;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NUMLIST;
    temp[2].type = 1;
    temp[2].datum.terminal.token = CLOSEBRAKET;
    Rule FaVob = {3, {temp[0], temp[1], temp[2]}};
    table[FACTOR][OPENBRAKET] = FaVob;

    // <Factor-Tail> -- (
    temp[0].type = 1;
    temp[0].datum.terminal.token = OPENPAREN;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ACTUALS;
    temp[2].type = 1;
    temp[2].datum.terminal.token = CLOSEPAREN;
    Rule FatOp = {3, {temp[0], temp[1], temp[2]}};
    table[FACTORTAIL][OPENPAREN] = FatOp;

    // <Factor-Tail> --  )
    temp[0].type = 3;
    Rule FatCp = {1, {temp[0]}};
    table[FACTORTAIL][CLOSEPAREN] = FatCp;

    // <Factor-Tail> --  {
    temp[0].type = 3;
    Rule FatOc = {1, {temp[0]}};
    table[FACTORTAIL][OPENCURL] = FatOc;

    // <Factor-Tail> --  }
    temp[0].type = 3;
    Rule FatCc = {1, {temp[0]}};
    table[FACTORTAIL][CLOSECURL] = FatCc;

    // <Factor-Tail> --  ,
    temp[0].type = 3;
    Rule FatCm = {1, {temp[0]}};
    table[FACTORTAIL][COMMA] = FatCm;

    // <Factor-Tail> --  ;
    temp[0].type = 3;
    Rule FatSc = {1, {temp[0]}};
    table[FACTORTAIL][SEMICOLON] = FatSc;

    // <Factor-Tail> --  *
    temp[0].type = 3;
    Rule FatTm = {1, {temp[0]}};
    table[FACTORTAIL][TIMES] = FatTm;

    // <Factor-Tail> --  /
    temp[0].type = 3;
    Rule FatDv = {1, {temp[0]}};
    table[FACTORTAIL][DIVIDE] = FatDv;

    // <Factor-Tail> --  =
    temp[0].type = 1;
    temp[0].datum.terminal.token = EQUALS;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    Rule FatEq = {2, {temp[0], temp[1]}};
    table[FACTORTAIL][EQUALS] = FatEq;

    // <Factor-Tail> --  -
    temp[0].type = 3;
    Rule FatMn = {1, {temp[0]}};
    table[FACTORTAIL][MINUS] = FatMn;

    // <Factor-Tail> --  +
    temp[0].type = 3;
    Rule FatPl = {1, {temp[0]}};
    table[FACTORTAIL][PLUS] = FatPl;

    // <Factor-Tail> --  <
    temp[0].type = 3;
    Rule FatLs = {1, {temp[0]}};
    table[FACTORTAIL][LESS] = FatLs;

    // <Factor-Tail> -- ==
    temp[0].type = 3;
    Rule FatEE = {1, {temp[0]}};
    table[FACTORTAIL][DEQUALS] = FatEE;

    // <Factor-Tail> -- and
    temp[0].type = 3;
    Rule FatAd = {1, {temp[0]}};
    table[FACTORTAIL][AND] = FatAd;

    // <Factor-Tail> -- or
    temp[0].type = 3;
    Rule FatOr = {1, {temp[0]}};
    table[FACTORTAIL][OR] = FatOr;

    // <Factor-Tail> -- ]
    temp[0].type = 3;
    Rule FatCb = {1, {temp[0]}};
    table[FACTORTAIL][CLOSEBRAKET] = FatCb;

    // <Factor-Tail> -- [
    temp[0].type = 1;
    temp[0].datum.terminal.token = OPENBRAKET;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGN;
    temp[2].type = 1;
    temp[2].datum.terminal.token = CLOSEBRAKET;
    Rule FatOb = {3, {temp[0], temp[1], temp[2]}};
    table[FACTORTAIL][OPENBRAKET] = FatOb;

    // <Assign> --(
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsOp = {2, {temp[0], temp[1]}};
    table[ASSIGN][OPENPAREN] = AsOp;

    // <Assign> --!
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsEx = {2, {temp[0], temp[1]}};
    table[ASSIGN][EXCLAIM] = AsEx;

    // <Assign> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsMn = {2, {temp[0], temp[1]}};
    table[ASSIGN][MINUS] = AsMn;

    // <Assign> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsId = {2, {temp[0], temp[1]}};
    table[ASSIGN][IDENTIFIER] = AsId;

    // <Assign> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsInt = {2, {temp[0], temp[1]}};
    table[ASSIGN][INTEGER] = AsInt;

    // <Assign> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsBool = {2, {temp[0], temp[1]}};
    table[ASSIGN][BOOLEAN] = AsBool;

    // <Assign> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsOb = {2, {temp[0], temp[1]}};
    table[ASSIGN][OPENBRAKET] = AsOb;

    // <Assign> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = ASSIGNTAIL;
    Rule AsVb = {2, {temp[0], temp[1]}};
    table[ASSIGN][VOPENBRAKET] = AsVb;

    // <Assign-Tail> -- ;
    temp[0].type = 1;
    temp[0].datum.terminal.token = SEMICOLON;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = EXPR;
    Rule AstSc = {2, {temp[0], temp[1]}};
    table[ASSIGNTAIL][SEMICOLON] = AstSc;

    // <Assign-Tail> -- ]
    temp[0].type = 3;
    Rule AstCb = {1, {temp[0]}};
    table[ASSIGNTAIL][CLOSEBRAKET] = AstCb;
    
    // <Actuals> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActOp = {1, {temp[0]}};
    table[ACTUALS][OPENPAREN] = ActOp;

    // <Actuals> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActEx = {1, {temp[0]}};
    table[ACTUALS][EXCLAIM] = ActEx;

    // <Actuals> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActMn = {1, {temp[0]}};
    table[ACTUALS][MINUS] = ActMn;

    // <Actuals> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActId = {1, {temp[0]}};
    table[ACTUALS][IDENTIFIER] = ActId;

    // <Actuals> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActInt = {1, {temp[0]}};
    table[ACTUALS][INTEGER] = ActInt;

    // <Actuals> -- Boolean
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActBool = {1, {temp[0]}};
    table[ACTUALS][BOOLEAN] = ActBool;

    // <Actuals> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActOb = {1, {temp[0]}};
    table[ACTUALS][OPENBRAKET] = ActOb;

    // <Actuals> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEACTUALS;
    Rule ActVb = {1, {temp[0]}};
    table[ACTUALS][VOPENBRAKET] = ActVb;

    // <Actuals> -- )
    temp[0].type = 3;
    Rule ActCp = {1, {temp[0]}};
    table[ACTUALS][CLOSEPAREN] = ActCp;

    // <NEActuals> -- (
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaOp = {2, {temp[0], temp[1]}};
    table[NEACTUALS][OPENPAREN] = NeaOp;

    // <NEActuals> -- !
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaEx = {2, {temp[0], temp[1]}};
    table[NEACTUALS][EXCLAIM] = NeaEx;

    // <NEActuals> -- -
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaMn = {2, {temp[0], temp[1]}};
    table[NEACTUALS][MINUS] = NeaMn;

    // <NEActuals> -- Id
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaId = {2, {temp[0], temp[1]}};
    table[NEACTUALS][IDENTIFIER] = NeaId;

    // <NEActuals> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaInt = {2, {temp[0], temp[1]}};
    table[NEACTUALS][INTEGER] = NeaInt;

    // <NEActuals> -- [
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaOb = {2, {temp[0], temp[1]}};
    table[NEACTUALS][OPENBRAKET] = NeaOb;

    // <NEActuals> -- v[
    temp[0].type = 0;
    temp[0].datum.nonTerminal = EXPR;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEATAIL;
    Rule NeaVb = {2, {temp[0], temp[1]}};
    table[NEACTUALS][VOPENBRAKET] = NeaVb;

    // <NEA-Tail> -- )
    temp[0].type = 3;
    Rule NeatCp = {1, {temp[0]}};
    table[NEATAIL][CLOSEPAREN] = NeatCp;

    // <NEA-Tail> -- ,
    temp[0].type = 1;
    temp[0].datum.terminal.token = COMMA;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEACTUALS;
    Rule NeatCm = {2, {temp[0], temp[1]}};
    table[NEATAIL][COMMA] = NeatCm;

    // <NumList> -- ;
    temp[0].type = 3;
    Rule NlSc = {1, {temp[0]}};
    table[NUMLIST][SEMICOLON] = NlSc;

    // <NumList> -- ]
    temp[0].type = 3;
    Rule NlCb = {1, {temp[0]}};
    table[NUMLIST][CLOSEBRAKET] = NlCb;

    // <NumList> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NENUMLIST;
    Rule NlInt = {1, {temp[0]}};
    table[NUMLIST][INTEGER] = NlInt;

    // <NENumList> -- Integer
    temp[0].type = 1;
    temp[0].datum.terminal.token = INTEGER;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NENTAIL;
    Rule NenlInt = {2, {temp[0], temp[1]}};
    table[NENUMLIST][INTEGER] = NenlInt;

    // <NENTAIL> -- ;
    temp[0].type = 3;
    Rule NentSc = {1, {temp[0]}};
    table[NENTAIL][SEMICOLON] = NentSc;

    // <NENTAIL> -- ]
    temp[0].type = 3;
    Rule NentCb = {1, {temp[0]}};
    table[NENTAIL][CLOSEBRAKET] = NentCb;

    // <NENTAIL> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NENUMLIST;
    Rule NentInt = {1, {temp[0]}};
    table[NENTAIL][INTEGER] = NentInt;

    // <VctList> -- ;
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEVLIST;
    Rule VlSc = {1, {temp[0]}};
    table[VCTLIST][SEMICOLON] = VlSc;

    // <VctList> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NEVLIST;
    Rule VlInt = {1, {temp[0]}};
    table[VCTLIST][INTEGER] = VlInt;

    // <VctList> -- ]
    temp[0].type = 3;
    Rule VlCb = {1, {temp[0]}};
    table[VCTLIST][CLOSEBRAKET] = VlCb;

    // <NEVList> -- ;
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NUMLIST;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEVLTAIL;
    Rule NevlSc = {2, {temp[0], temp[2]}};
    table[NEVLIST][SEMICOLON] = NevlSc;

    // <NEVList> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NUMLIST;
    temp[1].type = 0;
    temp[1].datum.nonTerminal = NEVLTAIL;
    Rule NevlInt = {2, {temp[0], temp[2]}};
    table[NEVLIST][INTEGER] = NevlInt;

    // <NEVList> -- ]
    temp[0].type = 3;
    Rule NevlCb = {1, {temp[0]}};
    table[NEVLIST][CLOSEBRAKET] = NevlCb;

    // <NEVLTail> -- ;
    temp[0].type = 3;
    Rule NevltSc = {1, {temp[0]}};
    table[NEVLTAIL][SEMICOLON] = NevltSc;

    // <NEVLTail> -- ]
    temp[0].type = 3;
    Rule NevltCb = {1, {temp[0]}};
    table[NEVLTAIL][CLOSEBRAKET] = NevltCb;

    // <NEVLTail> -- Integer
    temp[0].type = 0;
    temp[0].datum.nonTerminal = NENUMLIST;
    Rule NevltInt = {1, {temp[0]}};
    table[NEVLTAIL][INTEGER] = NevltInt;
}
