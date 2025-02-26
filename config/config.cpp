// Copyright (C) 2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include "config.h"

#include "../logging.h"
#include "config_reader.h"

using namespace std;

namespace config {
int use_qat_compress = 1;
int use_qat_uncompress = 1;
int use_iaa_compress = 0;
int use_iaa_uncompress = 0;
int use_zlib_compress = 1;
int use_zlib_uncompress = 1;
int iaa_compress_percentage = 50;
int iaa_decompress_percentage = 50;
int iaa_prepend_empty_block = 0;
int qat_periodical_polling = 0;
int qat_compression_level = 1;
std::string log_file = "";
int log_level = 2;

bool LoadConfigFile(std::string& file_content) {
  ConfigReader configReader;
  string file_name = "/etc/zlib/config/default_config";
  configReader.ParseFile(file_name);

  configReader.GetValue("use_qat_compress", use_qat_compress);
  configReader.GetValue("use_qat_uncompress", use_qat_uncompress);
  configReader.GetValue("use_iaa_compress", use_iaa_compress);
  configReader.GetValue("use_iaa_uncompress", use_iaa_uncompress);
  configReader.GetValue("use_zlib_compress", use_zlib_compress);
  configReader.GetValue("use_zlib_uncompress", use_zlib_uncompress);
  configReader.GetValue("iaa_compress_percentage", iaa_compress_percentage);
  configReader.GetValue("iaa_decompress_percentage", iaa_decompress_percentage);
  configReader.GetValue("iaa_prepend_empty_block", iaa_prepend_empty_block);
  configReader.GetValue("qat_periodical_polling", qat_periodical_polling);
  configReader.GetValue("qat_compression_level", qat_compression_level);
  configReader.GetValue("log_file", log_file);
  configReader.GetValue("log_level", log_level);

  file_content.append(configReader.DumpValues());

  return true;
}
}  // namespace config
