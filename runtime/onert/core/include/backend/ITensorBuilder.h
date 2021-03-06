/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ONERT_BACKEND_ITENSOR_BUILDER_H__
#define __ONERT_BACKEND_ITENSOR_BUILDER_H__

#include <map>

#include "ir/Index.h"
#include "ir/OperandInfo.h"
#include "ir/Operation.h"
#include "ir/Layout.h"
#include "ITensor.h"
#include "ITensorManager.h"
#include "ITensorRegistry.h"
#include "IDynamicTensorManager.h"

namespace onert
{
namespace backend
{

struct ITensorBuilder
{
  using IterateFunction = std::function<void(const ir::OperandIndex &)>;

  virtual ~ITensorBuilder(void) = default;

  /**
   * @brief Returns true if this TensorBuilder support dynamic tensor
   */
  virtual bool supportDynamicTensor() = 0;

  /**
   * @brief Register tensor information to allocate on backend
   *
   * @param ind Index
   * @param info Info
   * @param backend_layout Backend layout
   * @param as_const Whether this tensor is constant
   */
  virtual void registerTensorInfo(const ir::OperandIndex &ind, const ir::OperandInfo &info,
                                  ir::Layout backend_layout, bool as_const) = 0;
  /**
   * @brief Let the tensor builder know first use(start of lifetime) of a tensor
   *        Must be called before calling @c prepare
   *        Must be run up to once for each tensor before calling @c notifyLastUse
   *        NOTE: Useful only for static models
   */
  virtual void notifyFirstUse(const ir::OperandIndex &) = 0;
  /**
   * @brief Let the tensor builder know last use(end of lifetime) of a tensor
   *        Must be run up to once for each tensor after calling @c notifyFirstUse
   *        NOTE: Useful only for static models
   */
  virtual void notifyLastUse(const ir::OperandIndex &) = 0;
  /**
   * @brief Check if the tensor has been registered with @c registerTensorInfo
   *
   * @return true If the tensor has been registered
   * @return false Otherwise
   */
  virtual bool isRegistered(const ir::OperandIndex &) const = 0;
  /**
   * @brief Prepare the tensors
   *        Before calling this, all the tensors must be registered
   */
  virtual void prepare(void) = 0;
  /**
   * @brief Allocate the tensors
   *        Before calling this, @c prepare must be called
   */
  virtual void allocate() = 0;
  /**
   * @brief Some actions after functions' @c IFunction::prepare method.
   *        This is called right after each function's @c IFunction::prepare function has been
   *        called.
   */
  virtual void postFunctionPrepare() = 0;

  /**
   * @brief Get the tensor object
   *
   * @param ind Index of the tensor
   * @return std::shared_ptr<ITensor> The tensor object
   */
  virtual std::shared_ptr<ITensor> tensorAt(const ir::OperandIndex &ind) = 0;
  /**
   * @brief Iterate over tensors
   *
   * @param fn The function to be run
   */
  virtual void iterate(const IterateFunction &fn) = 0;

  /**
   * @brief Release static @c ITensorManger object which was built
   *        Before calling this, @c allocate must have been called
   *
   * @return std::unique_ptr<ITensorManager> Tensor Manager object
   */
  virtual std::unique_ptr<ITensorManager> releaseStaticTensorManager(void) = 0;

  /**
   * @brief Get dynamicTensorManager. If a backend does not support dynamic tensor, exception
   *        will be thrown.
   *
   * @return pointer of IDynamicTensorManager object
   *
   * @note   Since it is a pointer, its life time is from the cration of TensorBuilder
   *         to the end of execution
   */
  virtual IDynamicTensorManager *dynamicTensorManager(void)
  {
    throw std::runtime_error("dynamicTensorManager(): NYI");
  }

  /**
   * @brief Release dynamic @c ITensorManger object which was built
   *        Before calling this, @c allocate must have been called
   *
   * @return std::unique_ptr<ITensorManager> Tensor Manager object
   */
  virtual std::unique_ptr<ITensorManager> releaseDynamicTensorManager(void)
  {
    throw std::runtime_error("releaseDynamicTensorManager() for this backend is not supported");
  }

  /**
   * @brief Get tensor registry
   *
   * @return std::shared_ptr<backend::ITensorRegistry> tensor registry object
   *
   * @note   Backend should implement this when it has StaticTensorManager and DynamicTensorManager
   */
  virtual std::shared_ptr<backend::ITensorRegistry> tensorRegistry()
  {
    throw std::runtime_error("tensorRegistry(): NYI");
  }
};

} // namespace backend
} // namespace onert

#include <unordered_set>
#include <memory>

namespace onert
{
namespace backend
{

using TensorBuilderSet = std::unordered_set<std::shared_ptr<backend::ITensorBuilder>>;

} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_ITENSOR_BUILDER_H__
