# Compare-and-Swap vs Ticket Lock

## Objective
Implement CAS-based spinlock and fair ticket lock using atomic operations.

---

## Files
- cas_lock.c → CAS-based spinlock
- ticket_lock.c → Fair ticket lock
- output/ → Execution screenshots

---

## CAS Lock
- Uses atomic_compare_exchange_strong()
- Not fair (no ordering guarantee)
- Possible starvation

---

## Ticket Lock
- Uses atomic_fetch_add()
- Ensures FIFO ordering
- Fair and no starvation

---

## Comparison

| Feature        | CAS Lock        | Ticket Lock      |
|----------------|----------------|------------------|
| Fairness       | No             | Yes              |
| Starvation     | Possible       | No               |
| Order          | Random         | Sequential       |

---

## How to Run

```bash
gcc cas_lock.c -o cas -pthread
gcc ticket_lock.c -o ticket -pthread

./cas
./ticket
