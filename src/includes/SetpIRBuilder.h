#ifndef _SETPIRBUILDER_H_
#define _SETPIRBUILDER_H_

#include "BaseIRBuilder.h"
#include "EflagsBuilder.h"
#include "Inst.h"
#include "OneOperandTemplate.h"


class SetpIRBuilder: public BaseIRBuilder, public OneOperandTemplate {

  public:
    SetpIRBuilder(uint64_t address, const std::string &disassembly);

    // From BaseIRBuilder
    virtual Inst *process(AnalysisProcessor &ap) const;

    // From OneOperandTemplate
    virtual void none(AnalysisProcessor &ap, Inst &inst) const;

    virtual void reg(AnalysisProcessor &ap, Inst &inst) const;

    virtual void imm(AnalysisProcessor &ap, Inst &inst) const;

    virtual void mem(AnalysisProcessor &ap, Inst &inst) const;
};

#endif // _SETPIRBUILDER_H_
