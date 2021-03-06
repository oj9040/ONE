function(_GEMMLowpSource_import)
  nnas_include(ExternalSourceTools)
  nnas_include(OptionTools)

  # NOTE TensorFlow 1.12 uses the following URL
  envoption(EXTERNAL_DOWNLOAD_SERVER "https://github.com")
  set(GEMMLOWP_URL ${EXTERNAL_DOWNLOAD_SERVER}/google/gemmlowp/archive/38ebac7b059e84692f53e5938f97a9943c120d98.tar.gz)
  ExternalSource_Get("gemmlowp" ${DOWNLOAD_GEMMLOWP} ${GEMMLOWP_URL})

  set(GEMMLowpSource_DIR ${gemmlowp_SOURCE_DIR} PARENT_SCOPE)
  set(GEMMLowpSource_FOUND ${gemmlowp_SOURCE_GET} PARENT_SCOPE)
endfunction(_GEMMLowpSource_import)

_GEMMLowpSource_import()
