#!/usr/bin/env ruby
# -*- coding: utf-8 -*-
#
#  TOPPERS Software
#      Toyohashi Open Platform for Embedded Real-Time Systems
# 
#  Copyright (C) 2016-2019 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
# 
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
# 
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
# 
#  $Id: testcfg.rb 645 2019-12-09 16:50:28Z ertl-hiro $
# 

Encoding.default_external = 'utf-8'
require "pp"

#
#  テストプログラム毎に必要なオプションの定義
#
CFG_TEST_SPEC = {
  # ビルドに成功するテスト
  "cfg_all1"   => { },
  "cfg_all2"   => { },
  "cfg_attmod1"   => { SYSOBJ: "test_attmod3", \
								APPLOBJ: "test_attmod1 test_attmod2" },
  "cfg_attsec1"   => { },
  "cfg_attsec2"   => { },
  "cfg_attsec3"   => { },
  "cfg_stdreg1"   => { OPTS: "-t",
                       APPLOBJ: "test_attmod0 test_attmod1 test_attmod2 " \
								"test_attmod3 test_attmod4 test_attmod5" },
  "cfg_stdreg2"   => { OPTS: "-t",
                       APPLOBJ: "test_attmod0 test_attmod1 test_attmod2 " \
								"test_attmod3 test_attmod4 test_attmod5" },
  "cfg_stdreg3"   => { OPTS: "-t",
                       APPLOBJ: "test_attmod0 test_attmod1 test_attmod2 " \
								"test_attmod3 test_attmod4 test_attmod5" },
  "cfg_stdreg4"   => { OPTS: "-t",
                       APPLOBJ: "test_attmod0 test_attmod1 test_attmod2 " \
								"test_attmod3 test_attmod4 test_attmod5" },
  "cfg_stdreg5"   => { OPTS: "-t",
                       APPLOBJ: "test_attmod0 test_attmod1 test_attmod2 " \
								"test_attmod3 test_attmod4 test_attmod5" },
}

WARNING_TEST_SPEC = {
  # 警告は出るがビルドに成功するテスト
  "cfg_warning1"  => { },
}

PASS4_TEST_SPEC = {
  # パス4でエラーになるテスト
  "pass4_all1" => { },
  "pass4_all2" => { },
}

PASS2_TEST_SPEC = {
  # パス2でエラーになるテスト
  "pass2_cfg1" => { },
  "pass2_cfg2" => { },
  "pass2_cls1" => { },
  "pass2_dom1" => { },
  "pass2_int1" => { },
  "pass2_mbf1" => { },
  "pass2_mbf2" => { },
  "pass2_mem1" => { },
  "pass2_obj1" => { },
  "pass2_obj2" => { },
  "pass2_obj3" => { },
  "pass2_obj4" => { },
  "pass2_scy1" => { },
  "pass2_scy2" => { },
  "pass2_spn1" => { },
  "pass2_spn2" => { },
  "pass2_task1" => { },
  "pass2_task2" => { },
  "pass2_task3" => { },

  "pass2_mml1" => { TARGET: 1 },
}

PASS1_TEST_SPEC = {
  # パス1でエラーになるテスト
}

#
#  カーネルライブラリの作成
#
def BuildKernel
  if !Dir.exist?("KERNELLIB")
    Dir.mkdir("KERNELLIB")
  end

  Dir.chdir("KERNELLIB") do
    puts("== building: KERNELLIB ==")
    configCommand = "ruby #{$usedSrcDir}/configure.rb"
    configCommand += " #{$targetOptions[0]}"
    configCommand += " -c empty.cfg"
    puts(configCommand)
    system(configCommand)
    system("touch empty.cfg")
    system("make libkernel.a")
    if File.exist?("Makefile.bak")
      File.delete("Makefile.bak")
    end
  end
end

#
#  テストプログラムの作成
#
def BuildTest(test, testSpec, errorRedirect, mkdirFlag=false, rmFlag=false)
  objDir = test.tr("a-z_", "A-Z-")

  if !Dir.exist?(objDir)
    if mkdirFlag
      Dir.mkdir(objDir)
    else
      return
    end
  end

  Dir.chdir(objDir) do
    if rmFlag
      puts("== removing timestamp files: #{objDir} ==")
      system("rm *.timestamp")
    end

    puts("== building: #{objDir} ==")
    configCommand = "ruby #{$usedSrcDir}/configure.rb"
    if testSpec.has_key?(:TARGET)
      configCommand += " #{$targetOptions[testSpec[:TARGET]]}"
    else
      configCommand += " #{$targetOptions[0]}"
    end
    configCommand += " -a #{$usedSrcDir}/test_cfg"

    if (!testSpec.has_key?(:TARGET) || testSpec[:TARGET] == 0)
      configCommand += " -L ../KERNELLIB"
    end
    if testSpec.has_key?(:SRC)
      configCommand += " -A #{testSpec[:SRC]}"
    else
      configCommand += " -A #{test}"
    end
    if testSpec.has_key?(:CFG)
      configCommand += " -c #{testSpec[:CFG]}.cfg"
    end
    if testSpec.has_key?(:SYSOBJ)
      configCommand += " -S \"" \
			+ testSpec[:SYSOBJ].split(/\s+/).map{|f| f+".o"}.join(" ") \
			+ "\""
    end
    if testSpec.has_key?(:APPLOBJ)
      configCommand += " -U \"" \
			+ testSpec[:APPLOBJ].split(/\s+/).map{|f| f+".o"}.join(" ") \
			+ "\""
    end
    if testSpec.has_key?(:DEFS)
      configCommand += " -O \"#{testSpec[:DEFS]}\""
    end
    if testSpec.has_key?(:OPTS)
      configCommand += " #{testSpec[:OPTS]}"
    end
    puts(configCommand)
    system(configCommand)

    makeCommand = "make"
    if errorRedirect
      makeCommand += " 2> error.txt"
    end
    system(makeCommand)

    if File.exist?("Makefile.bak")
      File.delete("Makefile.bak")
    end
  end
end

#
#  全テストプログラムの作成
#
def BuildAll
  CFG_TEST_SPEC.each do |test, testSpec|
    BuildTest(test, testSpec, false)
  end
  WARNING_TEST_SPEC.each do |test, testSpec|
    BuildTest(test, testSpec, true, false, true)
  end
  PASS4_TEST_SPEC.each do |test, testSpec|
    BuildTest(test, testSpec, true)
  end
  PASS2_TEST_SPEC.each do |test, testSpec|
    BuildTest(test, testSpec, true)
  end
  PASS1_TEST_SPEC.each do |test, testSpec|
    BuildTest(test, testSpec, true)
  end
end

#
#  ファイルの比較
#
def diffFile(test, filename)
  diffCommand = "diff #{$usedSrcDir}/test_cfg/#{test}/#{filename} #{filename}"
  puts(diffCommand)
  system(diffCommand)
end

#
#  テスト結果のチェック（パス3まで通過するテスト）
#
def CfgTest(test, testSpec)
  objDir = test.tr("a-z_", "A-Z-")
  return unless Dir.exist?(objDir)

  Dir.chdir(objDir) do
    puts("== checking: #{objDir} ==")
    diffFile(test, "kernel_cfg.h")
    diffFile(test, "kernel_cfg.c")
    diffFile(test, "kernel_mem.c")
    diffFile(test, "ldscript.ld")
  end
end

#
#  テスト結果のチェック（途中でエラーになるテスト）
#
def ErrorTest(test, testSpec)
  objDir = test.tr("a-z_", "A-Z-")
  return unless Dir.exist?(objDir)

  Dir.chdir(objDir) do
    puts("== checking: #{objDir} ==")
    diffFile(test, "error.txt")
  end
end

#
#  全テストプログラムのテスト結果のチェック
#
def ExecAll
  CFG_TEST_SPEC.each do |test, testSpec|
    CfgTest(test, testSpec)
  end
  WARNING_TEST_SPEC.each do |test, testSpec|
    ErrorTest(test, testSpec)
  end
  PASS4_TEST_SPEC.each do |test, testSpec|
    ErrorTest(test, testSpec)
  end
  PASS2_TEST_SPEC.each do |test, testSpec|
    ErrorTest(test, testSpec)
  end
  PASS1_TEST_SPEC.each do |test, testSpec|
    ErrorTest(test, testSpec)
  end
end

#
#  カーネルライブラリのクリーン
#
def CleanKernel
  if Dir.exist?("KERNELLIB")
    Dir.chdir("KERNELLIB") do
      system("make clean")
    end
  end
end

#
#  テストプログラムのクリーン
#
def CleanTest(test, testSpec)
  objDir = test.tr("a-z_", "A-Z-")
  return unless Dir.exist?(objDir)

  Dir.chdir(objDir) do
    system("make clean")
    system("rm error.txt")
  end
end

#
#  全テストプログラムのクリーン
#
def CleanAll
  CFG_TEST_SPEC.each do |test, testSpec|
    CleanTest(test, testSpec)
  end
  WARNING_TEST_SPEC.each do |test, testSpec|
    CleanTest(test, testSpec)
  end
  PASS4_TEST_SPEC.each do |test, testSpec|
    CleanTest(test, testSpec)
  end
  PASS2_TEST_SPEC.each do |test, testSpec|
    CleanTest(test, testSpec)
  end
  PASS1_TEST_SPEC.each do |test, testSpec|
    CleanTest(test, testSpec)
  end
end

#
#  ソースディレクトリ名を取り出す
#
if /^(.*)\/test_cfg\/testcfg/ =~ $0
  $srcDir = $1
else
  $srcDir = "."
end

if /^\// =~ $srcDir
  $usedSrcDir = $srcDir
else
  $usedSrcDir = "../" + $srcDir
end

#
#  ターゲット依存のオプションを読む
#
$targetOptions = {}
File.open("TARGET_OPTIONS") do |file|
  file.each_line.with_index do |line, index|
    line.chomp!
    $targetOptions[index] = line
  end
end

#
#  パラメータで指定された処理の実行
#
if ARGV.size == 0
  BuildKernel()
  BuildAll()
  ExecAll()
else
  ARGV.each do |param|
    case param
    when "kernel"
      BuildKernel()
    when "build"
      BuildAll()
    when "exec"
      ExecAll()
    when "all"
      BuildAll()
      ExecAll()
    when "clean_kernel"
      CleanKernel()
    when "clean"
      CleanKernel()
      CleanAll()
    else
      if CFG_TEST_SPEC.has_key?(param)
        BuildTest(param, CFG_TEST_SPEC[param], false, true)
        CfgTest(param, CFG_TEST_SPEC[param])
      elsif WARNING_TEST_SPEC.has_key?(param)
        BuildTest(param, WARNING_TEST_SPEC[param], true, true, true)
        ErrorTest(param, WARNING_TEST_SPEC[param])
      elsif PASS4_TEST_SPEC.has_key?(param)
        BuildTest(param, PASS4_TEST_SPEC[param], true, true)
        ErrorTest(param, PASS4_TEST_SPEC[param])
      elsif PASS2_TEST_SPEC.has_key?(param)
        BuildTest(param, PASS2_TEST_SPEC[param], true, true)
        ErrorTest(param, PASS2_TEST_SPEC[param])
      elsif PASS1_TEST_SPEC.has_key?(param)
        BuildTest(param, PASS1_TEST_SPEC[param], true, true)
        ErrorTest(param, PASS1_TEST_SPEC[param])
      else
        puts("invalid parameter: #{param}")
      end
    end
  end
end
