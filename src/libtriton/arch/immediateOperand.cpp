//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#include <cpuSize.hpp>
#include <immediateOperand.hpp>



namespace triton {
  namespace arch {

    ImmediateOperand::ImmediateOperand() {
      this->value = 0;
    }


    ImmediateOperand::ImmediateOperand(triton::uint64 value, triton::uint32 size /* bytes */) {

      if (size == 0)
        throw std::runtime_error("ImmediateOperand::ImmediateOperand(): size cannot be zero.");

      if (size != BYTE_SIZE && size != WORD_SIZE && size != DWORD_SIZE && size != QWORD_SIZE && size != DQWORD_SIZE && size != QQWORD_SIZE && size != DQQWORD_SIZE)
        throw std::runtime_error("ImmediateOperand::ImmediateOperand(): size must be aligned.");

      switch (size) {
        case BYTE_SIZE:
          this->value = (triton::uint8) value;
          break;
        case WORD_SIZE:
          this->value = (triton::uint16) value;
          break;
        case DWORD_SIZE:
          this->value = (triton::uint32) value;
          break;
        default:
          this->value = value;
      }

      this->setPair(std::make_pair(((size * BYTE_SIZE_BIT) - 1), 0));
    }


    ImmediateOperand::ImmediateOperand(const ImmediateOperand& other) : BitsVector(other) {
      this->copy(other);
    }


    ImmediateOperand::~ImmediateOperand() {
    }


    triton::uint64 ImmediateOperand::getValue(void) const {
      return this->value;
    }


    void ImmediateOperand::setValue(triton::uint64 v) {
      this->value = v;
    }


    triton::uint32 ImmediateOperand::getAbstractLow(void) const {
      return this->getLow();
    }


    triton::uint32 ImmediateOperand::getAbstractHigh(void) const {
      return this->getHigh();
    }


    triton::uint32 ImmediateOperand::getSize(void) const {
      return this->getVectorSize() / BYTE_SIZE_BIT;
    }


    triton::uint32 ImmediateOperand::getBitSize(void) const {
      return this->getVectorSize();
    }


    triton::uint32 ImmediateOperand::getType(void) const {
      return triton::arch::OP_IMM;
    }


    void ImmediateOperand::operator=(const ImmediateOperand& other) {
      BitsVector::operator=(other);
      this->copy(other);
    }


    void ImmediateOperand::copy(const ImmediateOperand& other) {
      this->value = other.value;
    }


    std::ostream& operator<<(std::ostream& stream, const ImmediateOperand& imm) {
      stream << "0x" << std::hex << imm.getValue() << ":" << std::dec << imm.getBitSize() << " bv[" << imm.getHigh() << ".." << imm.getLow() << "]";
      return stream;
    }


    std::ostream& operator<<(std::ostream& stream, const ImmediateOperand* imm) {
      stream << *imm;
      return stream;
    }


    bool operator==(const ImmediateOperand& imm1, const ImmediateOperand& imm2) {
      if (imm1.getValue() != imm2.getValue())
        return false;
      if (imm1.getSize() != imm2.getSize())
        return false;
      return true;
    }


    bool operator!=(const ImmediateOperand& imm1, const ImmediateOperand& imm2) {
      if (imm1 == imm2)
        return false;
      return true;
    }


    bool operator<(const ImmediateOperand& imm1, const ImmediateOperand& imm2) {
      return imm1.getValue() < imm2.getValue();
    }

  }; /* arch namespace */
}; /* triton namespace */
