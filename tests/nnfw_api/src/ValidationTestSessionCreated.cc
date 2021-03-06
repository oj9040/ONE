/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "NNPackages.h"
#include "fixtures.h"

TEST_F(ValidationTestSessionCreated, load_session_001)
{
  // Existing model must
  ASSERT_EQ(nnfw_load_model_from_file(
                _session, NNPackages::get().getModelAbsolutePath(NNPackages::ADD).c_str()),
            NNFW_STATUS_NO_ERROR);
}

TEST_F(ValidationTestSessionCreated, neg_load_session_001)
{
  ASSERT_EQ(nnfw_load_model_from_file(
                _session, NNPackages::get().getModelAbsolutePath("nonexisting_directory").c_str()),
            NNFW_STATUS_ERROR);
}

TEST_F(ValidationTestSessionCreated, neg_load_session_002)
{
  ASSERT_EQ(
      nnfw_load_model_from_file(nullptr, // session is null
                                NNPackages::get().getModelAbsolutePath(NNPackages::ADD).c_str()),
      NNFW_STATUS_ERROR);
}

TEST_F(ValidationTestSessionCreated, neg_prepare_001)
{
  // nnfw_load_model_from_file was not called
  ASSERT_EQ(nnfw_prepare(_session), NNFW_STATUS_ERROR);
}

TEST_F(ValidationTestSessionCreated, neg_run_001)
{
  // nnfw_load_model_from_file and nnfw_prepare was not called
  ASSERT_EQ(nnfw_run(_session), NNFW_STATUS_ERROR);
}
