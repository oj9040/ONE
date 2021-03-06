/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NNFW_TENSORBUILDER_H
#define NNFW_TENSORBUILDER_H

#include <unordered_map>

#include <backend/ITensorBuilder.h>
#include "ir/OperandIndexMap.h"

namespace onert
{
namespace backend
{
namespace hi_perf_cpu
{

class TensorBuilder : public ITensorBuilder
{
public:
  TensorBuilder();

private:
};

} // namespace hi_perf_cpu
} // namespace backend
} // namespace onert

#endif // NNFW_TENSORBUILDER_H
