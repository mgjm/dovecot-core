#ifndef __MBOX_INDEX_H
#define __MBOX_INDEX_H

#include "md5.h"
#include "mail-index.h"

typedef struct {
	MailIndex *index;
	MailFlags flags;
	const char **custom_flags;
	MD5Context md5;
	int received;
} MboxHeaderContext;

MailIndex *mbox_index_alloc(const char *dir, const char *mbox_path);

void mbox_header_init_context(MboxHeaderContext *ctx, MailIndex *index);
void mbox_header_func(MessagePart *part __attr_unused__,
		      const char *name, size_t name_len,
		      const char *value, size_t value_len,
		      void *context);
void mbox_keywords_parse(const char *value, size_t len,
			 const char *custom_flags[MAIL_CUSTOM_FLAGS_COUNT],
			 void (*func)(const char *, size_t, int, void *),
			 void *context);
int mbox_skip_crlf(IOBuffer *inbuf);
int mbox_mail_get_start_offset(MailIndex *index, MailIndexRecord *rec,
			       uoff_t *offset);

int mbox_index_rebuild(MailIndex *index);
int mbox_index_sync(MailIndex *index);
int mbox_index_fsck(MailIndex *index);
IOBuffer *mbox_open_mail(MailIndex *index, MailIndexRecord *rec);

int mbox_index_append(MailIndex *index, IOBuffer *inbuf);

time_t mbox_from_parse_date(const char *msg, size_t size);
const char *mbox_from_create(const char *sender, time_t time);

int mbox_index_rewrite(MailIndex *index);

#endif
