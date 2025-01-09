; ModuleID = 'program.bc'
source_filename = "program.bc"
target triple = "x86_64-pc-linux-gnu"

@"@.str" = private global [4 x i8] c"%d\0A\00"
@"@.str.1" = private global [4 x i8] c"%f\0A\00"
@"@.str.2" = private global [3 x i8] c"%d\00"
@"@.str.3" = private global [3 x i8] c"%f\00"

declare i32 @printf(ptr, i32)

declare i32 @__isoc99_scanf(ptr, ptr)

define void @escrevaInteiro(i32 %0) {
entry:
  %alloca = alloca i32, align 4
  store i32 %0, ptr %alloca, align 4
  %load = load i32, ptr %alloca, align 4
  %printf = call i32 @printf(ptr @"@.str", i32 %load)
  ret void
}

define void @escrevaFlutuante(float %0) {
entry:
  %alloca = alloca float, align 4
  store float %0, ptr %alloca, align 4
  %load = load float, ptr %alloca, align 4
  %fpext = fpext float %load to double
  %printf = call i32 @printf(ptr @"@.str.1", double %fpext)
  ret void
}

define void @leiaInteiro(ptr %0) {
entry:
  %alloca = alloca ptr, align 8
  store ptr %0, ptr %alloca, align 8
  %load = load ptr, ptr %alloca, align 8
  %__isoc99_scanf = call i32 @__isoc99_scanf(ptr @"@.str.2", ptr %load)
  ret void
}

define void @leiaFlutuante(ptr %0) {
entry:
  %alloca = alloca ptr, align 8
  store ptr %0, ptr %alloca, align 8
  %load = load ptr, ptr %alloca, align 8
  %__isoc99_scanf = call i32 @__isoc99_scanf(ptr @"@.str.3", ptr %load)
  ret void
}

define i32 @main() {
entry:
  %g = alloca [2 x float], align 4
  %h = alloca [1 x i32], align 4
  %ptr_element = getelementptr [2 x float], ptr %g, i32 0, i32 0
  store float 2.000000e+00, ptr %ptr_element, align 4
  %ptr_element1 = getelementptr [1 x i32], ptr %h, i32 0, i32 0
  store i32 1, ptr %ptr_element1, align 4
  %ptr_element2 = getelementptr [2 x float], ptr %g, i32 0, i32 1
  call void @leiaFlutuante(ptr %ptr_element2)
  %ptr_element3 = getelementptr [2 x float], ptr %g, i32 0, i32 0
  %g4 = load float, ptr %ptr_element3, align 4
  call void @escrevaFlutuante(float %g4)
  %ptr_element5 = getelementptr [1 x i32], ptr %h, i32 0, i32 0
  %h6 = load i32, ptr %ptr_element5, align 4
  call void @escrevaInteiro(i32 %h6)
  %ptr_element7 = getelementptr [2 x float], ptr %g, i32 0, i32 1
  %g8 = load float, ptr %ptr_element7, align 4
  call void @escrevaFlutuante(float %g8)
  ret i32 0
  ret i32 0
}
