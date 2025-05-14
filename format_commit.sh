#!/bin/bash
#这是一个样例 ./format_commit.sh ./commit_txt.txt

date=$(date +"%Y-%m-%d %H:%M:%S")
author=$(git config user.name)
email=$(git config user.email)

# 检查是否有文件参数
if [ $# -ge 1 ]; then
  content_file="$1"
  # 确保文件存在
  if [ ! -f "$content_file" ]; then
    echo "错误：文件 '$content_file' 不存在"
    exit 1
  fi
  content=$(cat "$content_file")
else
  # 未指定文件时手动输入内容
  echo "请输入变更内容（按 Ctrl+D 结束输入）："
  content=$(cat)
fi

commit_message="
Date:   $date
Author: $author <$email>
Change: 
$content
"

git commit -F - <<EOF
$commit_message
EOF