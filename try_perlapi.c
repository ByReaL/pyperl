/* DO NOT EDIT!!!
 * Autogenerated by ./try_perlapi.pl
 */


#include <EXTERN.h>
#define PERL_EXT 1
#include "perl.h"
#include <Python.h>

#include "try_perlapi.h"
#include "perlmodule.h"
#include "lang_lock.h"
#include "thrd_ctx.h"

static LOGOP dummy_op;

void fake_inittry()
{
    Zero(&dummy_op, 1, LOGOP);
    dummy_op.op_flags |= OPf_WANT_SCALAR;
    dummy_op.op_next = Nullop;
}

static void
fake_entertry()
{
    PERL_CONTEXT *cx;
    I32 gimme;
    dCTXP;

    PL_op = (OP*)&dummy_op;
    gimme = GIMME_V;

    ENTER;
    SAVETMPS;

//    Perl_push_return(aTHX_ Nullop);
    PUSHBLOCK(cx, (CXt_EVAL|CXp_TRYBLOCK), PL_stack_sp);
    PUSHEVAL(cx, 0);
    PL_eval_root = PL_op;
    PL_in_eval = EVAL_INEVAL;
    sv_setpvn(ERRSV, "", 0);
}

static void
fake_leavetry(I32 oldscope)
{
    dCTXP;
    if (PL_scopestack_ix > oldscope) {
        PERL_CONTEXT *cx;
        PMOP *newpm;
        I32 optype;
        SV **newsp;
        I32 gimme;

        POPBLOCK(cx,newpm);
        POPEVAL(cx);
//        Perl_pop_return(aTHX);
        PL_curpm = newpm;
    }

    FREETMPS;
    LEAVE;
}

int
try_array_len(AV* av)
{
    dJMPENV;
    dCTXP;
    int jmp_status;
    volatile I32 oldscope = PL_scopestack_ix;
    int RETVAL;

    ASSERT_LOCK_PERL;
    fake_entertry();

    JMPENV_PUSH(jmp_status);
    if (jmp_status == 0) {

        RETVAL = av_len(av)+1;

    }
    else if (jmp_status == 3) {
        /* caught an exception, $@ should be set */
        assert(SvTRUE(ERRSV));
        PYTHON_LOCK;
        propagate_errsv();
        PYTHON_UNLOCK;

        RETVAL = -1;
    }
    else {
        fprintf(stderr, "should not happen, jmp_status = %d\n", jmp_status);
    }
    JMPENV_POP;
    fake_leavetry(oldscope);
    return RETVAL;
}

SV**
try_av_fetch(AV* av, I32 key, I32 lval)
{
    dJMPENV;
    dCTXP;
    int jmp_status;
    volatile I32 oldscope = PL_scopestack_ix;
    SV** RETVAL;

    ASSERT_LOCK_PERL;
    fake_entertry();

    JMPENV_PUSH(jmp_status);
    if (jmp_status == 0) {

        RETVAL = av_fetch(av, key, lval);

    }
    else if (jmp_status == 3) {
        /* caught an exception, $@ should be set */
        assert(SvTRUE(ERRSV));
        PYTHON_LOCK;
        propagate_errsv();
        PYTHON_UNLOCK;

        RETVAL = NULL;
    }
    else {
        fprintf(stderr, "should not happen, jmp_status = %d\n", jmp_status);
    }
    JMPENV_POP;
    fake_leavetry(oldscope);
    return RETVAL;
}

int
try_SvGETMAGIC(SV* sv)
{
    dJMPENV;
    dCTXP;
    int jmp_status;
    volatile I32 oldscope = PL_scopestack_ix;
    int RETVAL;

    ASSERT_LOCK_PERL;
    fake_entertry();

    JMPENV_PUSH(jmp_status);
    if (jmp_status == 0) {

        SvGETMAGIC(sv);
        RETVAL = 0;

    }
    else if (jmp_status == 3) {
        /* caught an exception, $@ should be set */
        assert(SvTRUE(ERRSV));
        PYTHON_LOCK;
        propagate_errsv();
        PYTHON_UNLOCK;

        RETVAL = -1;
    }
    else {
        fprintf(stderr, "should not happen, jmp_status = %d\n", jmp_status);
    }
    JMPENV_POP;
    fake_leavetry(oldscope);
    return RETVAL;
}

int
try_SvSETMAGIC(SV* sv)
{
    dJMPENV;
    dCTXP;
    int jmp_status;
    volatile I32 oldscope = PL_scopestack_ix;
    int RETVAL;

    ASSERT_LOCK_PERL;
    fake_entertry();

    JMPENV_PUSH(jmp_status);
    if (jmp_status == 0) {

        SvSETMAGIC(sv);
        RETVAL = 0;

    }
    else if (jmp_status == 3) {
        /* caught an exception, $@ should be set */
        assert(SvTRUE(ERRSV));
        PYTHON_LOCK;
        propagate_errsv();
        PYTHON_UNLOCK;

        RETVAL = -1;
    }
    else {
        fprintf(stderr, "should not happen, jmp_status = %d\n", jmp_status);
    }
    JMPENV_POP;
    fake_leavetry(oldscope);
    return RETVAL;
}

