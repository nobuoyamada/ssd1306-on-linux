#!/bin/bash

# カーネルバージョンを動的に取得
KERNEL_VERSION=$(uname -r)

# モジュールのパスを設定
MODULE_DIR="/lib/modules/${KERNEL_VERSION}/extra"

# モジュールをロード
insmod ${MODULE_DIR}/ssd1306temp_dev.ko