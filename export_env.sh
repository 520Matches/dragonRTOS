#!/bin/bash
# 文件名：export_env.sh

# 设置环境变量（仅在当前shell生效）
# 可设置的ARCH有 {arm32, riscv32, arm64, riscv64}
export ARCH=riscv32

# 验证输出
echo "[INFO] 已设置环境变量: ARCH=$ARCH"
echo "[提示] 此配置仅在当前终端窗口有效"
