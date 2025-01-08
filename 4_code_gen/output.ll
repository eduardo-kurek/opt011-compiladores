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
  %a = alloca [10 x i32], align 4
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %repita

repita:                                           ; preds = %repita, %entry
  %i1 = load i32, ptr %i, align 4
  %multmp = mul i32 %i1, 3
  %i2 = load i32, ptr %i, align 4
  %ptr_element = getelementptr [10 x i32], ptr %a, i32 0, i32 %i2
  store i32 %multmp, ptr %ptr_element, align 4
  %i3 = load i32, ptr %i, align 4
  %addtmp = add i32 %i3, 1
  store i32 %addtmp, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %int2float = sitofp i32 %i4 to float
  %cmptmp = fcmp olt float %int2float, 1.000000e+01
  br i1 %cmptmp, label %repita, label %fim

fim:                                              ; preds = %repita
  store i32 0, ptr %i, align 4
  br label %repita5

repita5:                                          ; preds = %repita5, %fim
  %i7 = load i32, ptr %i, align 4
  %ptr_element8 = getelementptr [10 x i32], ptr %a, i32 0, i32 %i7
  %a9 = load i32, ptr %ptr_element8, align 4
  call void @escrevaInteiro(i32 %a9)
  %i10 = load i32, ptr %i, align 4
  %addtmp11 = add i32 %i10, 1
  store i32 %addtmp11, ptr %i, align 4
  %i12 = load i32, ptr %i, align 4
  %int2float13 = sitofp i32 %i12 to float
  %cmptmp14 = fcmp olt float %int2float13, 1.000000e+01
  br i1 %cmptmp14, label %repita5, label %fim6

fim6:                                             ; preds = %repita5
  ret i32 0
  ret i32 0
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
