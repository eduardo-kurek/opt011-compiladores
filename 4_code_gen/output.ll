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

define i32 @main() {
entry:
  %a = alloca [3 x [3 x i32]], align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %count = alloca i32, align 4
  store i32 0, ptr %count, align 4
  store i32 0, ptr %i, align 4
  br label %repita

repita:                                           ; preds = %fim2, %entry
  store i32 0, ptr %j, align 4
  br label %repita1

fim:                                              ; preds = %fim2
  store i32 0, ptr %i, align 4
  br label %repita15

repita1:                                          ; preds = %repita1, %repita
  %count3 = load i32, ptr %count, align 4
  %i4 = load i32, ptr %i, align 4
  %j5 = load i32, ptr %j, align 4
  %ptr_element = getelementptr [3 x [3 x i32]], ptr %a, i32 0, i32 %i4, i32 %j5
  store i32 %count3, ptr %ptr_element, align 4
  %count6 = load i32, ptr %count, align 4
  %addtmp = add i32 %count6, 1
  store i32 %addtmp, ptr %count, align 4
  %j7 = load i32, ptr %j, align 4
  %addtmp8 = add i32 %j7, 1
  store i32 %addtmp8, ptr %j, align 4
  %j9 = load i32, ptr %j, align 4
  %int2float = sitofp i32 %j9 to float
  %cmptmp = fcmp olt float %int2float, 3.000000e+00
  br i1 %cmptmp, label %repita1, label %fim2

fim2:                                             ; preds = %repita1
  %i10 = load i32, ptr %i, align 4
  %addtmp11 = add i32 %i10, 1
  store i32 %addtmp11, ptr %i, align 4
  %i12 = load i32, ptr %i, align 4
  %int2float13 = sitofp i32 %i12 to float
  %cmptmp14 = fcmp olt float %int2float13, 3.000000e+00
  br i1 %cmptmp14, label %repita, label %fim

repita15:                                         ; preds = %fim18, %fim
  store i32 0, ptr %j, align 4
  br label %repita17

fim16:                                            ; preds = %fim18
  ret i32 0
  ret i32 0

repita17:                                         ; preds = %repita17, %repita15
  %i19 = load i32, ptr %i, align 4
  %j20 = load i32, ptr %j, align 4
  %ptr_element21 = getelementptr [3 x [3 x i32]], ptr %a, i32 0, i32 %i19, i32 %j20
  %a22 = load i32, ptr %ptr_element21, align 4
  call void @escrevaInteiro(i32 %a22)
  %j23 = load i32, ptr %j, align 4
  %addtmp24 = add i32 %j23, 1
  store i32 %addtmp24, ptr %j, align 4
  %j25 = load i32, ptr %j, align 4
  %int2float26 = sitofp i32 %j25 to float
  %cmptmp27 = fcmp olt float %int2float26, 3.000000e+00
  br i1 %cmptmp27, label %repita17, label %fim18

fim18:                                            ; preds = %repita17
  %i28 = load i32, ptr %i, align 4
  %addtmp29 = add i32 %i28, 1
  store i32 %addtmp29, ptr %i, align 4
  %i30 = load i32, ptr %i, align 4
  %int2float31 = sitofp i32 %i30 to float
  %cmptmp32 = fcmp olt float %int2float31, 3.000000e+00
  br i1 %cmptmp32, label %repita15, label %fim16
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
