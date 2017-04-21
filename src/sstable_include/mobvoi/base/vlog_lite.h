#pragma once

#include "mobvoi/base/flags.h"
#include "mobvoi/base/log_lite.h"

DECLARE_int32(v);

namespace mobvoi {

#define VLOG(level) if ((level) <= FLAGS_v) LOG(INFO)

#define VLOG_IS_ON(verboselevel) (FLAGS_v >= (verboselevel))

}  // namespace mobvoi

