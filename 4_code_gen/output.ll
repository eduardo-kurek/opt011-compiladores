; ModuleID = 'program.bc'
source_filename = "program.bc"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"%f\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @escrevaInteiro(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  %3 = load i32, ptr %2, align 4
  %4 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %3)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @escrevaFlutuante(float noundef %0) #0 {
  %2 = alloca float, align 4
  store float %0, ptr %2, align 4
  %3 = load float, ptr %2, align 4
  %4 = fpext float %3 to double
  %5 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, double noundef %4)
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @leiaInteiro(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.2, ptr noundef %3)
  ret void
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @leiaFlutuante(ptr noundef %0) #0 {
  %2 = alloca ptr, align 8
  store ptr %0, ptr %2, align 8
  %3 = load ptr, ptr %2, align 8
  %4 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str.3, ptr noundef %3)
  ret void
}

define void @main() {
entry:
  %b = alloca [10 x [1 x float]], align 4
  %c = alloca float, align 4
  %ptr_element = getelementptr [10 x [1 x float]], ptr %b, i32 0, i32 2, i32 0
  store float 1.000000e+00, ptr %ptr_element, align 4
  %ptr_element1 = getelementptr [10 x [1 x float]], ptr %b, i32 0, i32 2, i32 0
  %b2 = load float, ptr %ptr_element1, align 4
  store float %b2, ptr %c, align 4
  %ptr_element3 = getelementptr [10 x [1 x float]], ptr %b, i32 0, i32 2, i32 0
  %b4 = load float, ptr %ptr_element3, align 4
  call void @escrevaFlutuante(float %b4)
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1, !2, !3, !4, !5}

!0 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{i32 7, !"frame-pointer", i32 2}
