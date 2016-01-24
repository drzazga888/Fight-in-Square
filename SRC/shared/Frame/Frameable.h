#ifndef FRAMEABLE_H
#define FRAMEABLE_H

#include "FrameGiveable.h"
#include "FrameApplyable.h"

/**
 * @brief
 * Klasa, która łączy dwie klasy abstrakcyjne,
 * które narzucają implementację metod
 * od przyjmowania ramek i ich produkowania.
 * Gdy klasa odziedziczy po Frameable, jest
 * wtedy "Ramkoprzyjmująca" i "Ramkodająca", czyli
 * po prostu jak sama nazwa mówi "Ramkowalna"
 */
class Frameable: public FrameGiveable, FrameApplyable {};

#endif
