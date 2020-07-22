// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "db/SnapshotVisitor.h"
#include "db/engine/SSExecutionEngine.h"
#include "scheduler/Definition.h"
#include "scheduler/job/SSSearchJob.h"
#include "scheduler/task/Task.h"

namespace milvus {
namespace scheduler {

// TODO(wxyu): rewrite
class XSSSearchTask : public Task {
 public:
    explicit XSSSearchTask(const server::ContextPtr& context, const std::string& dir_root,
                           const engine::SegmentVisitorPtr& visitor, TaskLabelPtr label);

    void
    Load(LoadType type, uint8_t device_id) override;

    void
    Execute() override;

 public:
    static void
    MergeTopkToResultSet(const engine::QueryResult& src_result, size_t src_k, size_t nq, size_t topk, bool ascending,
                         engine::QueryResult& tar_result);

 public:
    const server::ContextPtr context_;

    engine::SegmentVisitorPtr visitor_;

    engine::SSExecutionEnginePtr engine_ = nullptr;

    // distance -- value 0 means two vectors equal, ascending reduce, L2/HAMMING/JACCARD/TONIMOTO ...
    // similarity -- infinity value means two vectors equal, descending reduce, IP
    bool ascending_ = true;
};

}  // namespace scheduler
}  // namespace milvus