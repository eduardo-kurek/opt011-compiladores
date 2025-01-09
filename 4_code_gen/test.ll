; ModuleID = 'program.bc'
source_filename = "program.bc"
target triple = "x86_64-pc-linux-gnu"

@"@.str" = private global [4 x i8] c"%d\0A\00"
@"@.str.1" = private global [4 x i8] c"%f\0A\00"
@"@.str.2" = private global [3 x i8] c"%d\00"
@"@.str.3" = private global [3 x i8] c"%f\00"
@g = global [2 x float] zeroinitializer

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
  %h = alloca [1 x i32], align 4
  %i = alloca float, align 4
  store float 2.000000e+00, ptr @g, align 4
  %ptr_element = getelementptr [1 x i32], ptr %h, i32 0, i32 0
  store i32 1, ptr %ptr_element, align 4
  call void @leiaFlutuante(ptr %i)
  %g = load float, ptr @g, align 4
  call void @escrevaFlutuante(float %g)
  %ptr_element1 = getelementptr [1 x i32], ptr %h, i32 0, i32 0
  %h2 = load i32, ptr %ptr_element1, align 4
  call void @escrevaInteiro(i32 %h2)
  %i3 = load float, ptr %i, align 4
  call void @escrevaFlutuante(float %i3)
  ret i32 0
  ret i32 0
}
