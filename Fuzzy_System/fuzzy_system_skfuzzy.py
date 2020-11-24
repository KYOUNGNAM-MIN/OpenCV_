import numpy as np
import skfuzzy as fuzz
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'Malgun Gothic'

# 언어 변수 x, y, z (프로젝트 자금, 프로젝트 인력, 위험도)
x = np.arange(0, 101, 1)
y = np.arange(0, 101, 1)
z = np.arange(0, 101, 1)

# 퍼지 멤버십 함수 영역 정의
# A1, A2, A3: 논의 영역 x 상에 대한 퍼지 집합에서 정해지는 언어 값
A1 = fuzz.trapmf(x, [0, 0, 30, 40])
A2 = fuzz.trimf(x, [30, 50, 70])
A3 = fuzz.trapmf(x, [60, 70, 100, 100])
# B1, B2: 논의 영역 y 상에 대한 퍼지 집합에서 정해지는 언어 값
B1 = fuzz.trapmf(y, [0, 0, 20, 70])
B2 = fuzz.trapmf(y, [30, 80, 100, 100])
# C1, C2, C3: 논의 영역 z 상에 대한 퍼지 집합에서 정해지는 언어 값
C1 = fuzz.trapmf(z, [0, 0, 30, 40])
C2 = fuzz.trapmf(z, [30, 45, 55, 70])
C3 = fuzz.trapmf(z, [60, 70, 100, 100])

# 그래프 시각화
fig, (ax0, ax1, ax2) = plt.subplots(nrows=3, figsize=(8, 9))

ax0.plot(x, A1, 'b', linewidth=1.5, label='부족하다')
ax0.plot(x, A2, 'g', linewidth=1.5, label='한계 수익점에 있다')
ax0.plot(x, A3, 'r', linewidth=1.5, label='충분하다')
ax0.set_title('프로젝트 자금')
ax0.legend()

ax1.plot(y, B1, 'b', linewidth=1.5, label='적다')
ax1.plot(y, B2, 'g', linewidth=1.5, label='많다')
ax1.set_title('프로젝트 인력')
ax1.legend()

ax2.plot(z, C1, 'b', linewidth=1.5, label='낮다')
ax2.plot(z, C2, 'g', linewidth=1.5, label='중간이다')
ax2.plot(z, C3, 'r', linewidth=1.5, label='높다')
ax2.set_title('위험도')
ax2.legend()

for ax in (ax0, ax1, ax2):
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.get_xaxis().tick_bottom()
    ax.get_yaxis().tick_left()

plt.tight_layout()

# 전문가가 설정한 크리스프 입력 값
# x1: 35%, y1: 60%
x1 = 35
y1 = 60

# 퍼지화 수행
uxA1 = fuzz.interp_membership(x, A1, x1)
uxA2 = fuzz.interp_membership(x, A2, x1)
uxA3 = fuzz.interp_membership(x, A3, x1)
uyB1 = fuzz.interp_membership(y, B1, y1)
uyB2 = fuzz.interp_membership(y, B2, y1)

# 규칙 평가
# 규칙1: IF 프로젝트 자금이 충분하다. OR 프로젝트 인력이 적다. THEN 위험도가 낮다.
# 규칙2: IF 프로젝트 자금이 한계 수익점에 있다. AND 프로젝트 인력이 많다. THEN 위험도가 중간이다.
# 규칙3: IF 프로젝트 자금이 부족하다. THEN 위험도가 높다.
# 찾아낸 범위에서 필요없는 상단의 범위를 fmin을 사용해서 잘라낸다.
# OR는 fmax로, AND는 fmin으로 계산한다.

# 규칙1: IF x가 A3 OR y가 B1, THEN z는 C1
rule1 = np.fmax(uxA3, uyB1)
rule1 = np.fmin(rule1, C1)

# 규칙2: IF x가 A2 AND y가 B2, THEN z는 C2
rule2 = np.fmin(uxA2, uyB2)
rule2 = np.fmin(rule2, C2)

# 규칙3: IF x가 A1, THEN z가 C3
rule3 = np.fmin(uxA1, C3)
z0 = np.zeros_like(z)

# 규칙 평가 후 그래프 시각화
fig, ax0 = plt.subplots(figsize=(8, 3))

ax0.fill_between(z, z0, rule1, facecolor='b', alpha=0.7)
ax0.plot(z, C1, 'b', linewidth=0.5, linestyle='--', )
ax0.fill_between(z, z0, rule2, facecolor='g', alpha=0.7)
ax0.plot(z, C2, 'g', linewidth=0.5, linestyle='--')
ax0.fill_between(z, z0, rule3, facecolor='r', alpha=0.7)
ax0.plot(z, C3, 'r', linewidth=0.5, linestyle='--')
ax0.set_title('규칙 평가 후 Output')

for ax in (ax0,):
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.get_xaxis().tick_bottom()
    ax.get_yaxis().tick_left()

plt.tight_layout()

# 규칙 후건의 통합
aggregated = np.fmax(rule1, np.fmax(rule2, rule3))

# 역퍼지화
# Defuzzified 결과 계산 (실제 답): z1
# 'centroid' mode: 면적의 중심
z1 = fuzz.defuzz(z, aggregated, 'centroid')
z_activation = fuzz.interp_membership(z, aggregated, z1)

print("-----------------------------")
print("z1: ", z1)
print("-----------------------------")

# 최종 통합 그래프 시각화
fig, ax0 = plt.subplots(figsize=(8, 3))

ax0.plot(z, C1, 'b', linewidth=0.5, linestyle='--', )
ax0.plot(z, C2, 'g', linewidth=0.5, linestyle='--')
ax0.plot(z, C3, 'r', linewidth=0.5, linestyle='--')
ax0.fill_between(z, z0, aggregated, facecolor='yellow', alpha=0.7)
ax0.plot([z1, z1], [0, z_activation], 'k', linewidth=1.5, label='크리스프 결과 값', alpha=0.9)
ax0.legend()
ax0.set_title('최종 통합 그래프')

for ax in (ax0,):
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.get_xaxis().tick_bottom()
    ax.get_yaxis().tick_left()

plt.tight_layout()

plt.show()