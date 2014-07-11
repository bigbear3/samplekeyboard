/*
 * Copyright (C) 2013, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LATINIME_PROBABILITY_DICT_CONTENT_H
#define LATINIME_PROBABILITY_DICT_CONTENT_H

#include <cstdint>
#include <cstdio>

#include "defines.h"
#include "suggest/policyimpl/dictionary/structure/v4/content/single_dict_content.h"
#include "suggest/policyimpl/dictionary/structure/v4/content/terminal_position_lookup_table.h"
#include "suggest/policyimpl/dictionary/structure/v4/ver4_dict_constants.h"
#include "suggest/policyimpl/dictionary/utils/buffer_with_extendable_buffer.h"

namespace latinime {

class ProbabilityEntry;

class ProbabilityDictContent : public SingleDictContent {
 public:
    ProbabilityDictContent(uint8_t *const buffer, const int bufferSize,
            const bool hasHistoricalInfo, const bool isUpdatable)
            : SingleDictContent(buffer, bufferSize, isUpdatable),
              mHasHistoricalInfo(hasHistoricalInfo),
              mSize(getBuffer()->getTailPosition() / getEntrySize()) {}

    ProbabilityDictContent(const bool hasHistoricalInfo)
            : mHasHistoricalInfo(hasHistoricalInfo), mSize(0) {}

    const ProbabilityEntry getProbabilityEntry(const int terminalId) const;

    bool setProbabilityEntry(const int terminalId, const ProbabilityEntry *const probabilityEntry);

    bool flushToFile(FILE *const file) const;

    bool runGC(const TerminalPositionLookupTable::TerminalIdMap *const terminalIdMap,
            const ProbabilityDictContent *const originalProbabilityDictContent);

 private:
    DISALLOW_COPY_AND_ASSIGN(ProbabilityDictContent);

    int getEntrySize() const;

    int getEntryPos(const int terminalId) const;

    bool writeEntry(const ProbabilityEntry *const probabilityEntry, const int entryPos);

    bool mHasHistoricalInfo;
    int mSize;
};
} // namespace latinime
#endif /* LATINIME_PROBABILITY_DICT_CONTENT_H */
